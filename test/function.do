func hello () ~
  out "hello world"
endfunc

func pi() ~
  return 3.14
endfunc

$PI = pi()
out $PI
