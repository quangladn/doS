# doS | do script

doS is written in c++ which is an intpreter programming language

## installation
pls install c++ and javac if you want build code


### usage intpreter
```
doS <path>
```

### usage dowload package
```
# i don't know how can i run java in cmd without going to directory :0)
java dpm package_name
```

## docs

#### hello world
```
out "hello, world!"
```

#### variable, user input

##### variable
```
$name = "quangladn"
```

##### user input
```
get "what's your name: " $name
out $name
```

#### if else
```
if 1 == 1 ~
  out "1==1"
else ~
  out "1 != 1"
endif
```
#### loop

##### while
```
while 1 == 1 ~
  get "chat: " $message
  if $message == "#exit" ~
    break
  else ~
    if $message == "@hello" ~
      out "hello world"
    else ~
      out $message
  endif
endloop
```

##### for
```
for $i=0; $i < 11; $i++ ~
  out "hello world"
endloop
```

#### debug
```
$test = "hello world"
#out $test
```
#### function
```
func fName() ~
  out "test function"
endfunc
func PI() ~
  return 3.14
endfunc
func getName($name) ~
  return $name
endFUnc
fName()
$PI = PI()
out $PI
out "\n"
get "name: " $name
$saveName = getName($name)
```
