# doS | do script

doS is written in c++ which is an intpreter programming language

## installation
pls install c++ if you want build code

#### windows
i dont know add path in command prompt

#### linux macos
```
./publish/install/linux_mac.sh
```

#### unix
```
./publish/install/unix.sh
```

### usage
```
doS <path>
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
