declblock {
    int A[100];
    int n, mid;
    int t, i, j;
}

codeblock {
    read n;
    for i=1,n {
        A[i] = i;
    }

    for i=1,n {
        print A[i], "";
    }

    println "";

    mid = n/2;

    for i=1,mid {
        j = (n-i)+1;
        println "Swapping", i, j;
        t = A[i];
        A[i] = A[j];
        A[j] = t;
    }

    for i=1,n {
        print A[i], "";
    }

    println "";
}
