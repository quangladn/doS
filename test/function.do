func hello () ~
  out "hello world"
endfunc

func pi() ~
  return 3.14
endfunc

func send_hello($name) ~
  return $name
endfunc

$test = send_hello("quang")
out $test

