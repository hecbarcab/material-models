import sympy as sym
import sympy.utilities.codegen as cgen
import sympy.codegen.rewriting as copt
import numpy as np
import re

'''
Computes the gradient of f w.r.t. the given variables.
'''
def gradient(f, v):
    return sym.Matrix([f]).jacobian(v)

'''
Computes the hessian of f w.r.t. the given variables.
'''
def hessian(f, v):
    return sym.hessian(f, v)

'''
Helper tables that relate variable types and dimensions to specific Eigen types.
'''
DTypeToEigen = { "double": "d", "float": "f", "int": "i" }
NDimsToEigen = [ "%s%.0s", "%.0sVectorX%s", "%.0sMatrixX%s" ]
    
'''
Helper function to convert a generated SymPy variable to its corresponding
Eigen type. Also performs the changes necessary to ensure column-major access
to the data.
'''
def convert_var_to_eigen(var, lines, output=False):
    name = str(var.name)
    shape = [] if var.dimensions is None else [ 1+siz for _, siz in var.dimensions if siz != 0 ]
    ndims = len(shape)
    dtype = var.get_datatype('c')
    mtype = NDimsToEigen[ndims] % (dtype, DTypeToEigen[dtype])
    
    # Replace definition of variable (for vector and matrix result types).
    lines = [ line.replace(dtype + ' *' + str(var.name), ("const " if not output else "") + mtype + '& ' + str(var.name)) for line in lines ]
    
    # If the variable is an output, initialize with correct shape before assigning.
    if output is True and ndims > 0:
        index = np.where([ ("%s[0] =" % name) in line for line in lines ])[0][0]
        lines.insert(index, "    %s.resize(%s);" % (name, ", ".join([ str(size) for size in shape ])))

    # In case the result is a matrix, use Eigen's parenthesis operator to access
    # the data. NOTE: Assume SymPy outputs row major matrices. Might not be the
    # case.
    if ndims == 2:
        for j in range(len(lines)):
            match = re.search('%s\[([0-9]+)\]' % name, lines[j])
            if match:
                idx = int(match.group(1))
                col = idx % shape[0]
                row = idx // shape[1]
                lines[j] = lines[j][:match.start(1)-1] + ("(%i, %i)" % (row, col)) + lines[j][match.end(1)+1:]

    # Done!
    return lines
    
'''
Given a set of SymPy symbols, generates the corresponding C++ code to evaluate
them in runtime.
'''
def generate(export):
    
    # Generate code from exported routines.
    generator = cgen.CCodeGen(cse=True)
    routines = [ generator.routine(name, copt.optimize(sym.simplify(expr), copt.optims_c99), None, None) for name, expr in export]
    codes = [ generator.write((routine,), "", header=False, empty=True) for routine in routines ]
    codes = [ code for (_, code), (_, _) in codes ]
    
    # Sanitize generated code.
    for i in range(len(codes)):
        
        # Split code into lines. Remove include ones.
        lines = codes[i].split('\n')
        lines = lines[3:]
        
        # Reindent from 3 spaces to 4 spaces :|
        lines = [ line.replace('   ', '    ') for line in lines ]
        
        # Convert input and output argument variables to Eigen types.       
        for var in routines[i].arguments:
            lines = convert_var_to_eigen(var, lines, var in routines[i].result_variables)

        # Rename result variable to something legible.
        result = routines[i].result_variables[-1]
        name = str(result.name) if result.dimensions is not None else str(routines[i].name) + '_result'
        lines = [ line.replace(name, 'out') for line in lines ]
                
        # Rejoin code.
        codes[i] = '\n'.join(lines)
        
    # Done!
    return codes
    
'''
Saves the given string to a file.
'''
def save(fname, str):
    with open(fname, "w") as f:
        f.write(str)