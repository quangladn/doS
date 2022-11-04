#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;

vector<string> tokens = {};
map<string, string> varlist;                  // "$a": "test"
map<vector<string>, vector<string>> funcList; // { {name,"$arg"}: {"out","hello world"} }

int errorInLexer = 0;
int lineL = 1;
string fileName;
// functional
void assignVar(string varName, string value)
{
    int foundVar = 0;
    for (auto var_ : varlist)
    {
        if (varName == var_.first)
        {
            foundVar = 1;
            break;
        }
    }
    if (foundVar == 0)
    {
        varlist[varName] = value;
    }
    else
    {
        map<string, string>::iterator it = varlist.find(varName);
        if (it != varlist.end())
            it->second = value;
    }
}

string findVar(string varName, int line)
{
    int foundVar = 0;
    string data;
    for (auto var_ : varlist)
    {
        if (varName == var_.first)
        {
            data = var_.second;
            foundVar = 1;
            break;
        }
    }
    if (foundVar == 0)
    {
        cout << "VarError: Var \'" << varName << "\' not found, line: " << line << endl;
        data = "";
    }
    return data;
}

void getInput(string question, string varName)
{
    string value;
    cout << question;
    //    cin >> value;
    getline(cin, value);
    // cout << value << endl;
    assignVar(varName, value);
    cin.clear();
}

void debug_(int isLoop, int skipIf, int line)
{
    for (auto item : varlist)
    {
        cout << "variable " << item.first << " : " << item.second << endl;
    }
    cout << "isLoop: " << isLoop << endl;
    cout << "skipIf: " << skipIf << endl;
    cout << "line: " << line << endl;
    cout << "stop# ";
    string a;
    cin >> a;
    cin.clear();
}

void createFunc(string func_name, vector<string> arg, vector<string> code)
{
    // try {

    vector<string> init = {func_name};
    for (int i = 0; i < arg.size(); i++)
    {
        init.push_back(arg[i]);
    }
    funcList[init] = code;
}

vector<string> getFunc(string funcName, int line, vector<string> arg)
{
    int foundFunc = 0;
    vector<string> code__ = {};
    for (auto f : funcList)
    {
        if (funcName == (f.first)[0])
        {
            // if ((f.first).size() > 1)
            // {
            for (int j = 1; j < (f.first).size(); j++)
            {
                if ((f.first)[j] != "")
                {
                    assignVar((f.first)[j], arg[j - 1]);
                }
            }
            // }

            for (int i = 0; i < f.second.size(); i++)
            {
                code__.push_back((f.second)[i]);
            }
            foundFunc = 1;
            break;
        }
        // cout << (f.first)[0] << " | \n" << (f.second) << endl;
    }
    if (foundFunc == 0)
    {
        cout << "FuncError: Func \'" << funcName << "\' not found, line: " << line << endl;
    }
    return code__;
    code__.clear();
}

void lexer(string ftxt,vector <string> &tokens)
{
    ftxt += "\n";

    // init variabe
    string token;
    string str_;
    string num;
    string var_;
    string funcParam;
    string token_;
    string funcName = "";
    string module_name = "";
    int isFuncName = 0;
    int varStarted = 0;
    int stateSkipSpace = 0;
    int isFuncParama = 0;
    int module_get = 0;
    // lexer
    for (int i = 0; ftxt[i] != 0; i++)
    {
        token += ftxt[i];
        token_ = ftxt[i];
        if (token == "\n" and stateSkipSpace == 0 or token == "\r")
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }
            if (module_get == 1)
            {
              module_get =0;
              tokens.push_back(module_name);
              module_name ="";
            }

            tokens.push_back("nl");
            token = "";
        }
        else if (token == " ")
        {
            if (stateSkipSpace == 0)
            {
                token = "";
            }
            else if (stateSkipSpace == 1)
            {
                token = " ";
            }
        }
        else if (token == ";" and stateSkipSpace == 0)
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }

            tokens.push_back(";");
            token = "";
        }
        else if (token == "," and stateSkipSpace == 0)
        {
            if (isFuncParama == 1)
            {

                tokens.push_back(funcParam);
                funcParam = "";
            }

            else
            {
                cout << "File \"" << fileName << "\", line " << lineL << endl;
                cout << "\t \'"
                     << ","
                     << "\'" << endl;
                cout << "SyntaxError: Invalid syntax" << endl;
                errorInLexer = 1;
            }
            token = "";
        }
        else if (token == "<" and stateSkipSpace == 0)
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }

            tokens.push_back("less");
            token = "";
        }
        else if (token == "=" and stateSkipSpace == 0)
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }

            if (tokens[tokens.size() - 1] == "equals")
            {
                tokens[tokens.size() - 1] = "eqeq";
            }
            else
            {
                tokens.push_back("equals");
            }
            token = "";
        }
        else if (token == "+" or token == "-") // or token == "*" or token == "/" )
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }
            else
            {
            }

            if (tokens[tokens.size() - 1] == "+" and token == "+")
                tokens[tokens.size() - 1] = "++";
            else if (tokens[tokens.size() - 1] == "-" and token == "-")
                tokens[tokens.size() - 1] = "++";
            else
                tokens.push_back(token);
            token = "";
        }
        else if (token == "#" and stateSkipSpace == 0)
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }
            tokens.push_back("debug");
            token = "";
        }
        else if (token == "func" and stateSkipSpace == 0)
        {
            isFuncName = 1;
            tokens.push_back("func");
            token = "";
        }
        else if (token == "endfunc" and stateSkipSpace == 0)
        {
            isFuncName = 1;
            tokens.push_back("endfunc");
            token = "";
        }
        else if (token == "return" and stateSkipSpace == 0)
        {
            tokens.push_back("return");
            token = "";
        }
        else if (token == " " and stateSkipSpace == 0 and isFuncName == 1 or
                 token == " " and stateSkipSpace == 0 and isFuncParama == 1)
        {
            token = "";
        }
        else if (token == "\(" and stateSkipSpace == 0 and isFuncName == 1)
        {
            isFuncName = 0;
            tokens.push_back(funcName + "\(");
            isFuncParama = 1;
            token = "";
            funcName = "";
        }

        else if (token == ")" and stateSkipSpace == 0 and isFuncParama == 1)
        {
            tokens.push_back(funcParam);
            isFuncParama = 0;
            token = "";
            funcParam = "";
        }
        else if (token_ == "\(" and stateSkipSpace == 0)
        {
            tokens.push_back("callFunc");
            tokens.push_back(token);
            isFuncParama = 1;
            token = "";
            token_ = "";
        }
        else if (token == "module_import" and stateSkipSpace == 0)
        {
          module_get = 1;
          tokens.push_back("module_import");
          token = "";
        }
        else if (module_get == 1)
        {
          if (token == " ")
          {

          } else
          {

            module_name += token;
            token = "";
          }
        }
        else if (varStarted == 1)
        {
            var_ += token;
            token = "";
        }
        else if (token == "out" and stateSkipSpace == 0)
        {
            tokens.push_back("out");
            token = "";
        }
        else if (token == "if" and stateSkipSpace == 0)
        {
            tokens.push_back("if");
            token = "";
        }
        else if (token == "while" and stateSkipSpace == 0)
        {
            tokens.push_back("while");
            token = "";
        }
        else if (token == "for" and stateSkipSpace == 0)
        {
            tokens.push_back("for");
            token = "";
        }
        else if (token == "break" and stateSkipSpace == 0)
        {
            tokens.push_back("break");
            token = "";
        }
        else if (token == "endloop" and stateSkipSpace == 0)
        {
            tokens.push_back("endloop");
            token = "";
        }
        else if (token == "else" and stateSkipSpace == 0)
        {
            tokens.push_back("else");
            token = "";
        }
        else if (token == "~" and stateSkipSpace == 0)
        {
            if (num != "")
            {
                tokens.push_back(num);
                num = "";
            }
            if (var_ != "")
            {
                tokens.push_back(var_);
                var_ = "";
                varStarted = 0;
            }
            tokens.push_back("then");
            token = "";
        }
        else if (token == "endif" and stateSkipSpace == 0)
        {
            tokens.push_back("endif");
            token = "";
        }

        else if (token == "get" and stateSkipSpace == 0)
        {
            tokens.push_back("input");
            token = "";
        }
        else if (token == "\"" or token == " \"")
        {
            if (stateSkipSpace == 0)
            {
                stateSkipSpace = 1;
                token = "";
            }
            else if (stateSkipSpace == 1)
            {
                tokens.push_back(str_);
                str_ = "";
                stateSkipSpace = 0;
                token = "";
            }
        }
        else if (isFuncName == 1)
        {
            funcName += token;
            token = "";
        }
        else if (isFuncParama == 1)
        {
            funcParam += token;
            token = "";
        }
        else if (stateSkipSpace == 1)
        {
            str_ += token;
            token = "";
        }
        else if (token == "$" and stateSkipSpace == 0)
        {
            var_ += token;
            varStarted = 1;
            token = "";
        }
        else if (token == "1" or token == "2" or token == "3" or token == "4" or token == "5" or
                 token == "6" or token == "7" or token == "8" or token == "9" or token == "0" or token == ".")
        {
            num += token;
            token = "";
        }
    }
}

// test
void viewToken()
{
    for (int i = 0; i < tokens.size(); i++)
    {
        cout << "---\n";
        cout << "\'" << tokens[i] << "\'" << endl;
    }
}

void parse(char file[], vector<string> tokens, int line)
{
    string nameFunc;
    string funcParam;
    vector<string> arg;
    vector<string> code_;
    int i = 0;
    int skipIf = 0;
    int inLoop = 0;
    int isLoop = 0;
    int isFor = 0;
    int reLoop = 0;
    int inFunc = 0;
    while (i < tokens.size() and errorInLexer == 0)
    {
        if (inFunc == 1 and tokens[i] != "endfunc")
        {
            if (tokens[i] == "then")
            {
            }
            else
                code_.push_back(tokens[i]);
            i++;
        }
        else if (tokens[i] == "nl")
        {
            if (isLoop == 1)
            {
                inLoop++;
                i++;
                if (reLoop == 1)
                {
                }
                else
                    line++;
            }
            else
            {
                line++;
                i++;
            }
        }
        else if (tokens[i] == "debug")
        {
            if (isLoop == 1)
            {
                inLoop++;
            }
            debug_(isLoop, skipIf, line);
            // system("pause");
            i++;
        }
        else if (tokens[i] == "break")
        {
            if (skipIf == 1)
            {
                i++;
            }
            else
            {
                if (isLoop == 0)
                {
                    cout << "File \"" << file << "\", line " << line << endl;
                    cout << "\t \'" << tokens[i] << "\'" << endl;
                    cout << "SyntaxError: break outside loop" << endl;
                    break;
                }
                else if (isLoop == 1)
                {
                    isLoop = 0;
                    i++;
                }
            }
        }
        else if (tokens[i] == "out" and tokens[i + 1] != "nl")
        {
            if (skipIf == 1)
            {
                i += 2;
            }
            else
            {
                if (isLoop == 1)
                {
                    inLoop += 2;
                }
                string value = tokens[i + 1];
                if (value[0] == '$')
                {
                    value = findVar(value, line);
                }
                cout << value;
                i += 2;
            }
        }
        else if (tokens[i][0] == '$' and tokens[i + 1] == "equals")
        {
            string varName = tokens[i];
            if (skipIf == 1)
            {
                if (tokens[i + 2] == "callFunc")
                    i += 5;
                else
                    i += 3;
            }
            else
            {
                if (isLoop == 1)
                {
                    inLoop += 3;
                }
                string value = tokens[i + 2];
                if (value[0] == '$')
                {
                    value = findVar(value, line);
                    i++;
                }
                else if (value == "callFunc")
                {
                    string fName = tokens[i + 3];
                    if (tokens[i + 4] == "" and tokens[i + 5] == "nl")
                        i++;
                    else if (tokens[i + 4] == "" and tokens[i + 5] != "nl")
                    {
                        int skipParam = 1;
                        for (int j = i + 5; tokens[j] != "nl"; j++)
                        {
                            arg.push_back(tokens[j]);
                            skipParam++;
                        }

                        i += skipParam;
                    }
                    i += 2;
                    vector<string> codeInFunc = getFunc(fName, line, arg);
                    parse(file, codeInFunc, line);
                    codeInFunc.clear();
                    string sysOu = "$sysOutput";
                    value = findVar(sysOu, line);
                    arg.clear();
                }
                else
                {
                    i++;
                }
                assignVar(varName, value);
                i += 2;
            }
        }
        else if (tokens[i] == "input")
        {
            if (skipIf == 1)
            {
                i += 3;
            }
            else
            {
                string que = tokens[i + 1] + " ";
                string varName = tokens[i + 2];
                getInput(que, varName);
                i += 3;
                if (isLoop == 1)
                {
                    inLoop += 3;
                }
            }
        }
        else if (tokens[i] == "if" and tokens[i + 4] == "then")
        {
            if (isLoop == 1)
            {
                inLoop += 5;
            }
            if (skipIf == 1)
            {
                i += 5;
            }
            else if (skipIf == 0)
            {
                string value1 = tokens[i + 1];
                string value2 = tokens[i + 3];
                if (value1[0] == '$' and value2[0] or value1[0] == '$' or value2[0] == '$')
                {
                    if (value1[0] == '$')
                    {
                        value1 = findVar(value1, line);
                    }
                    if (value2[0] == '$')
                    {
                        value2 = findVar(value2, line);
                    }
                }
                string condition = tokens[i + 2];

                if (condition == "eqeq")
                {
                    if (value1 == value2)
                    {
                        // cout << "true" << endl;
                        skipIf = 0;
                    }
                    else
                    {
                        // cout << "false" << endl;
                        skipIf = 1;
                    }
                }
                else
                {
                    cout << "File \"" << file << "\", line " << line << endl;
                    cout << "\t \'" << tokens[i] << "\'" << endl;
                    cout << "SyntaxError: Unexpected token "
                         << "~" << endl;
                }
                i += 5;
            }
        }
        else if (tokens[i] == "else" and tokens[i + 1] == "then")
        {
            if (isLoop == 1)
            {
                inLoop += 2;
            }
            else
            {
            }
            if (skipIf == 1)
            {
                skipIf = 0;
                i += 2;
            }
            else if (skipIf == 0)
            {
                skipIf = 1;
                i += 2;
            }
            else
            {
                cout << "!codeError! skipIf have value is 0 or 1\n";
                break;
            }
        }

        else if (tokens[i] == "while" and tokens[i + 4] == "then")
        {
            if (skipIf == 1)
            {
                i += 5;
            }
            else
            {
                string value1 = tokens[i + 1];
                string value2 = tokens[i + 3];
                string condition = tokens[i + 2];
                i += 5;
                if (condition == "eqeq")
                {
                    if (value1 == value2)
                    {
                        isLoop = 1;
                    }
                    else
                    {
                        isLoop = 0;
                    }
                }
                else
                {

                    cout << "File \"" << file << "\", line " << line << endl;
                    cout << "   \'" << tokens[i] << "\'" << endl;
                    cout << "SyntaxError: Invalid token " << condition << endl;
                    break;
                }
            }
        }
        else if (tokens[i] == "for" and tokens[i + 4] == ";" and tokens[i + 8] == ";" and tokens[i + 11] == "then")
        {
            if (skipIf == 1)
            {
                i += 12;
            }
            if (isLoop == 1)
            {
                inLoop += 12;
            }
            else
            {
                int value;
                if (isFor == 0)
                {
                    value = atoi(tokens[i + 1].c_str());
                }
                else if (isFor == 1)
                {
                    value = atoi(findVar(tokens[i + 1], line).c_str());
                }
                else
                {
                    // cout << "1";
                }
                assignVar(tokens[i + 1], to_string(value));
                string condition = tokens[i + 6];
                if (condition == "less")
                {

                    if (atoi(findVar(tokens[i + 5], line).c_str()) < atoi(tokens[i + 7].c_str()) - 2)
                    {
                        isLoop = 1;
                        isFor = 1;
                        if (tokens[i + 10] == "++")
                        {
                            assignVar(tokens[i + 9], to_string(value + 1));
                        }
                        else if (tokens[i + 10] == "--")
                        {
                            assignVar(tokens[i + 9], to_string(value - 1));
                        }
                        else
                        {
                            cout << "File \"" << file << "\", line " << line << endl;
                            cout << "\t \'" << tokens[i] << "\'" << endl;
                            cout << "SyntaxError: Unexpected token "
                                 << "~" << endl;
                            break;
                        }
                        i += 12;
                    }
                    else
                    {
                        isLoop = 0;
                        i += 12;
                    }
                }
                else
                {
                    cout << "File \"" << file << "\", line " << line << endl;
                    cout << "\t \'" << tokens[i] << "\'" << endl;
                    cout << "\t \'" << tokens[i - 1] << "\'" << endl;
                    cout << "\t \'" << tokens[i + 1] << "\'" << endl;
                    cout << "SyntaxError: Unexpected token "
                         << "~" << endl;
                    break;
                }
            }
        }
        else if (tokens[i] == "func")
        {

            nameFunc = tokens[i + 1];
            int skipParam = 1;
            inFunc = 1;
            for (int j = i + 2; tokens[j] != "then"; j++)
            {
                arg.push_back(tokens[j]);
                skipParam++;
            }
            i += 2 + skipParam;
        }
        else if (tokens[i] == "endfunc")
        {
            inFunc = 0;
            createFunc(nameFunc, arg, code_);
            arg.clear();
            code_.clear();
            nameFunc = "";
            funcParam = "";
            i++;
        }
        else if (tokens[i] == "callFunc")
        {
            try
            {
                // string funcName = tokens[i+1];
                vector<string> codeInFunc = getFunc(tokens[i + 1], line, {});
                parse(file, codeInFunc, line);
                codeInFunc.clear();
                i += 2;
                if (tokens[i + 3] == "")
                    i++;
                parse(file, codeInFunc, line);
            }
            catch (const bad_alloc &)
            {
                cout << 1234 << endl;
            }
        }
        else if (tokens[i] == "return")
        {
            string re = tokens[i + 1];
            if (tokens[i + 1][0] == '$')
                re = findVar(tokens[i + 1], line);
            assignVar("$sysOutput", re);
            i += 2;
        }
        else if (tokens[i] == "module_import")
        {
            string ftxt;
            string code;
            string code_;
            vector <string> codes = {};
            string fName = "./modules_doS/"+tokens[i+1]+".do";
            // open file
            ifstream f(fName);
            while (getline(f,code))
            {
              //cout << code << endl;
              lexer(code,codes);
            }
            f.close();  
            parse(file,codes,line);
            codes.clear();
          i += 2;
        }
        else if (tokens[i] == "endloop")
        {
            int add;
            if (isFor == 0)
            {
                add = 5;
            }
            else if (isFor == 1)
            {
                add = 12;
            }
            isFor = 0;
            int sizeLoop = inLoop + add;
            if (isLoop == 1)
            {
                i -= sizeLoop;
                reLoop = 1;
                inLoop = 0;
            }
            else if (isLoop == 0)
            {
                i += sizeLoop + 1;
                reLoop = 0;
                inLoop = 0;
            }
            else
            {
            }
        }
        else if (tokens[i] == "endif")
        {
            if (isLoop == 1)
            {
                inLoop++;
            }
            else
            {
            }
            skipIf = 0;
            i++;
        }
        else
        {
            if (isLoop == 1)
            {
                i++;
            }
            else
            {
                cout << "File \"" << file << "\", line " << line << endl;
                cout << "\t \'" << tokens[i] << "\'" << endl;
                cout << "SyntaxError: Invalid syntax" << endl;
                i++;
                break;
            }
            // break;
        }
    }
}

int main(int argc, char *argv[])
{
    // try {
    if (argc == 1)
    {
        cout << "usage doS <path>" << endl;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-v") == 0)
        {
            cout << "beta-0.3: function update" << endl;
        }
        else
        {
            string ftxt;
            // open file
            ifstream file(argv[1]);
            if (file.is_open())
            {
                fileName = argv[1];
                while (getline(file, ftxt))
                {
                    if (errorInLexer == 1)
                    {
                        break;
                    }
                    else
                    {
                        // read file and create Token
                        lexer(ftxt,tokens);
                        lineL++;
                    }
                }
                // run parse

                parse(argv[1], tokens, 1);
                //viewToken();
                file.close();
            }
            else
            {
                cout << "FileNotFoud: File \'" << argv[1] << "\' not found" << endl;
            }
        }
    }
    return 0;
    //}
    /*catch (const bad_alloc&)
    {
      return -1;
    }*/
}
