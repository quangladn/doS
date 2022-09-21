while 1 == 1 ~
  get "> " $cmd
  if $cmd == "exit" ~
    break
  else ~
    if $cmd == "hello" ~
      out "hello world"
    else ~
      out $cmd
  endif
endloop
