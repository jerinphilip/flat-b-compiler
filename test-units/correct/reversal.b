declblock {
    int A[100];
    int n, mid;
    int t, i;
    int x;
}

codeblock {
    read n;
    for i=1,n {
        read A[i];
    }

    for i=1,n {
        print A[i], "";
    }

    mid = n/2;

    for i=1,mid {
        t = A[i];
        A[i] = A[n-i-1];
        A[n-i-1] = t;
    }

    for i=1,n {

    }
}
