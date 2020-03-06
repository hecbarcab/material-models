import sympy as sym
import sympy.utilities.codegen as cgen
import sympy.codegen.rewriting as copt
import numpy as np
import re

def gradient(f, v):
    return sym.Matrix([f]).jacobian(v)

def hessian(f, v):
    return sym.hessian(f, v)

def generate(export):
    # Handy constants.
    
    DTypeToEigen = { "double": "d", "float": "f", "int": "i" }
    NDimsToEigen = [ "%s%.0s", "%.0sVectorX%s", "%.0sMatrixX%s" ]
    
    # Generate code from exported routines.

    generator = cgen.CCodeGen(cse=True)
    routines = [ generator.routine(name, copt.optimize(sym.simplify(expr), copt.optims_c99), None, None) for name, expr in export]
    codes = [ generator.write((routine,), "", header=False, empty=True) for routine in routines ]
    codes = [ code for (_, code), (_, _) in codes ]
    
    # Sanitize generated code.

    for i in range(len(codes)):
        # Identify output of the routine and corresponding Eigen type.
        
        result = routines[i].result_variables[-1]
        shape = [] if result.dimensions is None else [ 1+siz for _, siz in result.dimensions if siz != 0 ]
        ndims = len(shape)
        dtype = result.get_datatype('c')
        mtype = NDimsToEigen[ndims] % (dtype, DTypeToEigen[dtype])
        
        # Split code into lines. Remove include ones.
        
        lines = codes[i].split('\n')
        lines = lines[3:]
        
        # Reindent from 3 spaces to 4 spaces :|
        
        lines = [ line.replace('   ', '    ') for line in lines ]
        
        # Replace name of output for something legible.
        
        name = str(result.name) if result.dimensions is not None else str(routines[i].name)+'_result'
        lines = [ line.replace(name, 'out') for line in lines ]
        
        # Replace definition of output variable (for vector and matrix result types).
        # Initialize with correct shape before assigning.
        
        if ndims > 0:
            lines = [ line.replace(dtype + ' *out', mtype + '& out') for line in lines ]
            index = np.where([ "out[0] =" in line for line in lines ])[0][0]
            lines.insert(index, "    out.resize(%s);" % ", ".join([ str(size) for size in shape ]))
                        
            # In case the result is a matrix, use Eigen's parenthesis operator to access
            # the data. NOTE: Assume SymPy outputs row major matrices. Might not be the
            # case.
            
            if ndims == 2:
                for j in range(len(lines)):
                    match = re.search('\[([0-9]+)\]', lines[j])
                    if match:
                        idx = int(match.group(1))
                        col = idx % shape[0]
                        row = idx // shape[1]
                        lines[j] = lines[j][:match.start(1)-1] + ("(%i, %i)" % (row, col)) + lines[j][match.end(1)+1:]
            
                
        # Rejoin code.

        codes[i] = '\n'.join(lines)
        
    # Done!

    return codes
    
def save(fname, str):
    with open(fname, "w") as f:
        f.write(str)