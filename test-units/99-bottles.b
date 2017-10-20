declblock{
	int i;
}

codeblock{
    i = 100;
    while ( i > 2 ){
        i = i - 1;
        println i, "bottles of beer on the wall!";
        println "Take one down, pass it around!";
    }

    println i, "bottles of beer on the wall!";
    println "Take one down, pass it around!";
    println "No more bottles of beer on the wall!";

}

