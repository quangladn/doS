while 1 == 1 ~
  get "> " $cmd
  if $cmd == "exit" ~
    break
  else ~
    out "j"
  if $cmd == "hello" ~
    out "hello world"
  else ~
    out "*"
    out $cmd
  endif
endloop
