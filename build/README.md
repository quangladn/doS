# install for windows

i tested on windows and it works but i have to rebuild and add the path manually

## build and auto add path
```
g++ src/doS.cpp -o build/doS
setx /M path "%path%;<path>"
```
