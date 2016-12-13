fun fizzbuzz(i::int) = 
  if (i mod 3 = 0) orelse (i mod 5 = 0) then
    if (i mod 3 = 0) then
      print("Fizz")
    else ()
    if (i mod 5 = 0) then
      print("Buzz")
    else ()
  else
    print(Int.toString(i)) 
  fizzbuzz(i+1)
  | fizzbuzz(100) = print("100")

fizzbuzz(1)
