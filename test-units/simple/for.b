declblock{
    int x;
    int y;
    int s, t[100];
}

codeblock{
L2: x = 0;
    for x = 1, 100 {
        t[x] = x;
    }

    for x = 1, 100 {
        println t[x-1];
    }
    println "....";
}

