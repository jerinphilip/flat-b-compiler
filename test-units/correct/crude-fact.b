declblock {
    int x;
    int y;
}

codeblock {
    x = 1;
    for y=1,10{
        x = x * y;
    }
    println "10!", "=", x; 
    println "Iterations: ", (y - 1);
    if (y == 10){
        println "Good";
    }
    else{
        println "Bad";
    }
}
