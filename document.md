# dev
If you want to help me with the code, here is the document for you
## environment for dev
- install c++
- if you use linux or osx then use make to build, if you use window then use bash by git to use make
- if you build for win pls build in /build/Windows, if build in osx or linux build in /build

## lexer
### note
When lexer token is add char from code, and if you want view token when run then it's below
code:
```
out "hello world"
```
token:
```
o
ou
out
 
"
"h
...
"hello world
\n
```
### add token
If your keyword has the following parameter as a variable or a number, use the following code
```
else if (token == "<keyword>") 
{
  tokens.push_back("<keyword>");
  token = "";
}
```
If keyword have front parameter then
```
else if (token == "<keyword>")
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
```

## parse
### note 
In parse there are few similarities but enough to code
### example
#### get
```
else if (tokens[i] == "input" and tokens[i+2][0] == '$')
{
  getInput(tokens[i+1],tokens[i+2])
  i+=3;
}
```

thank!
