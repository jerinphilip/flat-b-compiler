declblock {
    int product;
    int n;
    int i;
}

codeblock {
    read n;
    product = 1;
    for i=1,n {
        product = product * i;
    }

    println "Factorial", product;
    
}
