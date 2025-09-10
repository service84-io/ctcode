package s84.ctcode.transpiler.ctcode;

import s84.ctcode.system.ctcode.*;
import s84.ctcode.dbnf.ctcode.*;

public interface Transpiler {
    int Transpile(s84.ctcode.system.ctcode.System system, s84.ctcode.dbnf.ctcode.CTCodeFile ct_code_file, java.lang.String base_name);
}
