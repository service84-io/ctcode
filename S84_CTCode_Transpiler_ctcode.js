import * as S84_CTCode_System_ctcode from "./S84_CTCode_System_ctcode.js"
import * as S84_CTCode_dbnf_ctcode from "./S84_CTCode_dbnf_ctcode.js"

function ClearList(input) { input.length = 0; }
function Size(input) { return input.length; }
function Element(input, element) { return input[element]; }
function Append(input, element) { input.push(element); }
function ClearMap(input) { input.clear(); }
function SetKV(input, key, element) { input.set(key, element); }
function Keys(input) { return Array.from(input.keys()); }
function HasKV(input, key) { return input.has(key); }
function GetKV(input, key) { return input.get(key); }
function Length(input) { return input.length; }
function At(input, index) { return input[index]; }
function IntAt(input, index) { return input.charCodeAt(index); }
function Concat(left, right) { return left + right; }

export class OutputStream {
    WriteLine(line) {}
}

export class Transpiler {
    Transpile(system, ct_code_file, base_name) {}
}

