   //FizzBuzz
    var i:int;
    for i=0;i<=100;i++ {
        if i % 3 == 0 && i % 5 == 0{
           println("FizzBuzz\n")
        }else if i % 3 == 0{
           println("Fizz\n")
        }else if i % 5 == 0{
           println("Buzz\n")
        }else{
           println(i + "\n")
        }
    }
    