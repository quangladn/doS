#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

vector <string> tokens = {};
map <string, string> varlist;

void assignVar(string varName, string value)
{
    varlist[varName] = value;
}

string findVar(string varName, int line)
{
    int foundVar = 0;
    for (auto var_ : varlist)
    {
        if (varName == var_.first)
        {
            return var_.second;
            break;
        }
    }
    if (foundVar == 0)
    {
        cout << "VarError: Var \'" << varName << "\' not found, line: " << line << endl; 
        return "";
    }
}

void getInput(string question, string varName)
{
    string value;
    cout << question;
    cin >> value;
    assignVar(varName,value);
    cin.ignore();
}

void debug_(int isLoop,int skipIf,int line) 
{
  for (auto item : varlist)
  {
    cout << "variable " << item.first << " : " << item.second << endl;
  }
  cout << "isLoop: " << isLoop << endl;
  cout << "skipIf: " << skipIf << endl;
  cout << "line: " << line << endl;
  cout << "stop# ";
  cin;
  cin.ignore();
}

void lexer(string ftxt)
{
    ftxt += "\n";

    string token;
    string str_;
    string num;
    string var_;
    int varStarted = 0;
    int stateSkipSpace = 0;
    for (int i=0; ftxt[i] != 0; i++)
    {
        token += ftxt[i];
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
        else if (token == "+" or token == "-") //or token == "*" or token == "/" )
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

            if (tokens[tokens.size() - 1] == "+")
              tokens[tokens.size() - 1] = "++";
            else
              tokens.push_back(token);
            token = "";
        }
        else if (token == "$" and stateSkipSpace == 0)
        {
            var_ += token;
            varStarted = 1;
            token = "";
        }
        else if (varStarted == 1)
        {
            var_ += token;
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
        else if (stateSkipSpace == 1)
        {
            str_ += token;
            token = "";
        }
        else if (token == "1" or token == "2" or token == "3" or token == "4" or token == "5" or 
                token == "6" or token == "7" or token == "8" or token == "9" or token == "0" )
        {
            num += token;
            token = "";
        }
    }
}

void viewToken()
{
    for (int i=0; i < tokens.size(); i++)
    {
        cout << "---\n";
        cout << tokens[i] << endl;
    }
}

void parse(char file[])
{
    int i = 0;
    int line = 1;
    int skipIf = 0;
    int inLoop = 0;
    int isLoop = 0;
    int isFor = 0;
    int i_ = 1;
    while(i < tokens.size())
    {
        if (tokens[i] == "nl")
        {
                if (isLoop == 1)
                {
                    inLoop ++;
                    line --;
                    i++;
                }
                else {
                    line ++;
                    i ++;
                }
        }
        else if (tokens[i] == "debug")
        {
            if (isLoop == 1) { 
                inLoop ++;
            }
            debug_(isLoop,skipIf,line);
            //system("pause");
            i++;
            
        }
        else if (tokens[i] == "break" and isLoop == 1)
        {
            if (skipIf == 1)
            {
              inLoop ++;
              i++;
            }
            else {
                isLoop = 0;
                i ++;
            }
        }
        else if (tokens[i] == "")
        {
            if (skipIf == 1)
            {
                i ++;
            }
            else {

            if (isLoop == 1) { 
                inLoop ++;
              }
              i ++;
          }
        }
        else if (tokens[i] == "out")
        {
            if (skipIf == 1)
            {
                i += 2;
            }
            else 
            {
            if (isLoop == 1)
            {
                inLoop +=2;
            }
                    string value = tokens[i+1];
                    if (value[0] == '$')
                    {
                        value = findVar(value, line);
                    }
                    cout << value << endl;
                    i += 2;
            }
        }
        else if (tokens[i][0] == '$' and tokens[i+1] == "equals")
        {
            if (skipIf == 1)
            {
                i += 3;
            }
            else 
            {
            if (isLoop == 1)
            {
                inLoop += 3;
            }
                string value = tokens[i+2];
                if (value[0] == '$')
                {
                    value = findVar(value, line);
                }
                assignVar(tokens[i],value);
                i += 3;
            }
        }
        else if (tokens[i] == "input")
        {
            if (skipIf == 1)
            {
                i+=3;
            }
            else
            {
            if (isLoop == 1)
            {
                inLoop +=3;
            }
                string que = tokens[i+1] + " ";
                string varName = tokens[i+2];
                getInput(que, varName);
                i += 3; 
            }
        }
        else if (tokens[i] == "if" and tokens[i+4] == "then")
        {
            if (skipIf == 1)
            {
                i+=5;
            }
            else {
            if (isLoop == 1)
            {
                inLoop +=5;
            }
                string value1 = tokens[i+1];
                string value2 = tokens[i+3];
                if (value1[0] == '$' and value2[0] or value1[0] == '$' or value2[0] == '$')
                {
                  if (value1[0] == '$') {
                    value1 = findVar(value1,line);
                  }
                  if (value2[0] == '$') {
                    value2 = findVar(value2,line);
                  }
                }
                string condition = tokens[i+2];
    
                if (condition == "eqeq")
                {
                    if (value1 == value2)
                    {
                        //cout << "true" << endl;
                    }
                    else
                    {
                        //cout << "false" << endl;
                        skipIf = 1;
                    }
                }
                i+=5;
                
            }
        }
        else if (tokens[i] == "else" and tokens[i+1] == "then")
        {
            if (skipIf == 1)
            {
                skipIf = 0;
                i+=2;
            }
            else
            {
            if (isLoop == 1)
            {
                inLoop +=2;
            }
                skipIf = 1;
                i+=2;
            }
        }

        else if (tokens[i] == "while" and tokens[i+4] == "then")
        {
            //inLoop -= 4;
            if (skipIf == 1)
            {
                i += 5;
            }
            else
            {
                string value1 = tokens[i+1];
                string value2 = tokens[i+3];
                string condition = tokens[i+2];
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
                i += 5;
                
            }
        }
        else if (tokens[i] == "for" and tokens[i+4] == ";" and tokens[i+8] == ";" and tokens[i+11] == "then")
        {
          if (skipIf == 1) {
            i += 12;
          }
          else {
            int value;
            if (isFor == 0) {
              value = atoi(tokens[i+1].c_str());
            } else if (isFor == 1) {
              value = atoi(findVar(tokens[i+1],line).c_str());
            }
            else {
              cout << "";
            }
            assignVar(tokens[i+1],to_string(value));
            string condition = tokens[i+6];
            if (condition == "less") {

            if (atoi(findVar(tokens[i+5],line).c_str()) < atoi(tokens[i+7].c_str())-2) {
              isLoop = 1;
              isFor = 1;
              if (tokens[i+10] == "++") {
                assignVar(tokens[i+9],to_string(value+1));
              } 
              else if (tokens[i+10] == "--") {
                assignVar(tokens[i+9],to_string(value-1));
              }
              else {
                cout << line << endl;
                cout << "File \"" << file << "\", line " << line << endl;
                cout << "\t \'" << tokens[i] << "\'" << endl;
                cout << "SyntaxError: Unexpected token " << "~" << endl;
                i++;
                break;

              }
              i+=12;
            } 
            else {
              isLoop = 0;
              i+=12;
            }}
            else {
                cout << line << endl;
                cout << "File \"" << file << "\", line " << line << endl;
                cout << "\t \'" << tokens[i] << "\'" << endl;
                cout << "SyntaxError: Unexpected token " << "~" << endl;
                i++;
                break;
            }
          }
            
        }
        else if (tokens[i] == "endloop")
        { 
          int add;
          if (isFor == 0)
          {
            add = 5;
          } else if (isFor == 1)
          {
            add = 12;
          }
            int reLoop = inLoop + add;
            i_++;
            if (isLoop == 1)
            {
                i -= reLoop;
                inLoop = 0;
            }
            else if (isLoop == 0)
            {
                i += reLoop+1;
                inLoop = 0;
            }
            
            else if (isLoop == 0)
            {
                i += reLoop+1;
                inLoop = 0;
            }

        }
        else if (tokens[i] == "endif")
        { 
            if (isLoop == 1)
            {
                inLoop ++;
            }
            skipIf = 0;
            i++;
        }

        else 
        {
          cout << line << endl;
          cout << "File \"" << file << "\", line " << line << endl;
          cout << "\t \'" << tokens[i] << "\'" << endl;
          cout << "SyntaxError: invalid syntax" << endl;
          i++;
          break;
        }
    
    }
}


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << "usage doS <path>" << endl;
    }
    else if (argc == 2)
    {
      if (argv[1] == "-v") {
        cout << "beta-0.2.2: while update" << endl;
      }
      else {
        string ftxt;
        // open file
        ifstream file(argv[1]);
        if (file.is_open())
        {
            while (getline(file,ftxt))
            {
                // read file and create Token 
                lexer(ftxt);
            }
            // run parse 
            parse(argv[1]);
            //viewToken();
            file.close();
        }
        else
        {
          cout << "FileNotFoud: File \'" << argv[1] << "\' not found" << endl;
        }
      }
    }
    //cout << "hello world from doS" << endl;
    return 0;
}
