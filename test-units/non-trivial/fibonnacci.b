declblock {
    int a, b;
    int t, n;
}

codeblock {
    n = 12;
    a = 0;
    b = 1;
    while ( n > 0 ){
        t = a;
        a = b;
        b = b + t;
        println a, b;
        n = n - 1;
    }
    
}
