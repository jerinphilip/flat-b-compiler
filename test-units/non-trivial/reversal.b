declblock {
    int A[100];
    int n, mid;
    int t, i, j;
}

codeblock {
    n = 100;
    for i=0,(n-1) {
        A[i] = i;
    }

    for i=0,(n-1) {
        print A[i], "";
    }

    println "";

    mid = n/2;

    for i=0,(mid-1) {
        j = n-1-i;
        println "Swapping", i, j;
        t = A[i];
        A[i] = A[j];
        A[j] = t;
    }

    for i=0,(n-1) {
        print A[i], "";
    }

    println "";
}
