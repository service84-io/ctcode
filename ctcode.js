import * as fs from "fs";
import * as S84_CTCode_Main_ctcode from "./S84_CTCode_Main_ctcode.js";

class FileWriter {
    constructor(file_name) {
        this.file_name = file_name;
        fs.writeFileSync(this.file_name, "");
    }
    WriteLine(line) {
        fs.appendFileSync(this.file_name, line);
        fs.appendFileSync(this.file_name, "\n");
    }
}

class LoggerClass {
    WriteLine(line) { console.log(line); }
}

class System {
    ReadFileToString(file_name) { return fs.readFileSync(file_name, {encoding: 'ascii'}); }
    OpenFileWriter(file_name) { return new FileWriter(file_name); }
    GetLoggerDestination() { return new LoggerClass(); }
}

function main() {
    var system = new System();
    var main = new S84_CTCode_Main_ctcode.Main();
    var c_t_code_file_name = "";
    var transpiler_name = "";

    if (process.argv.length == 4) {
        c_t_code_file_name = process.argv[2];
        transpiler_name = process.argv[3];
    }
        
    process.exit(main.RunMain(system, c_t_code_file_name, transpiler_name));
}

main();
