# for dev
If you want to help me with the code, here is the document for you
## environment for dev
- install c++ 9+

## build

You need to build in "build/folder under os" and i will do the rest

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
If your keyword has the following parameter as a variable or a number, use the following code:
```
else if (token == "<keyword>") 
{
  tokens.push_back("<keyword>");
  token = "";
}
```
If keyword have front parameter:
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
else if (tokens[i] == "input")
{
  getInput(tokens[i+1],tokens[i+2])
  i+=3;
}
```

thank!
