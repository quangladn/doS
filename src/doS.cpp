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
        if (token == "\n" or token == "\r")
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
        
        else if (token == "=")
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

        else if (token == "$")
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

        else if (token == "out")
        {
            tokens.push_back("out");
            token = "";
        }
        else if (token == "if")
        {
            tokens.push_back("if");
            token = "";
        }
        else if (token == "else")
        {
            tokens.push_back("else");
            token = "";
        }
        else if (token == "~")
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
        else if (token == "endif")
        {
            tokens.push_back("endif");
            token = "";
        }

        else if (token == "get")
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
        cout << tokens[i] << endl;
    }
}

void parse()
{
    int i = 0;
    int line = 1;
    while(i < tokens.size())
    {
        if (tokens[i] == "nl")
        {
            line ++;
            i ++;
        }
        else if (tokens[i] == "out")
        {
            string value = tokens[i+1];
            if (value[0] == '$')
            {
                value = findVar(value, line);
            }
            cout << value << endl;
            i += 2;
        }
        else if (tokens[i][0] == '$')
        {
            string value = tokens[i+2];
            if (value[0] == '$')
            {
                value = findVar(value, line);
            }
            assignVar(tokens[i],value);
            i += 3;
        }
        else if (tokens[i] == "input")
        {
            string que = tokens[i+1] + " ";
            string varName = tokens[i+2];
            getInput(que, varName);
            i += 3;
        }

        else 
        {
            cout << "TokensError: Token \'" << tokens[i] << "\' is not link more token" << endl;
            i ++;
        }
    }

}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << "usage doS <path>" << endl;
    }
    else if (argc > 1)
    {
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
            //parse();
            viewToken();
            file.close();
        }
        else
        {
            cout << "FileNotFoud: File \'" << argv[1] << "\' not found" << endl;
        }
    }
    //cout << "hello world from doS" << endl;
    return 0;
}
