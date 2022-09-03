# doS | do script

doS is written in c++ which is an interpriter programming language

## installation
pls install c++ if you want build code

#### windows
Windows 7 or older is not supported.
i dont know add path in command prompt

#### linux macos
```
./publish/linux_mac.sh
```

#### unix
```
./publish/unix.sh
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
```
#### loop

##### while
```
while 1 == 1 ~
  get "chat: " $message
  out $message
endloop
```

##### for
updating...

