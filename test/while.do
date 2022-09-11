while 1 == 1 ~
  get "chat: " $a
  out $a
  if $a == "exit" ~
    break
  endif
endloop
