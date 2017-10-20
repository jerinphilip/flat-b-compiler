declblock {
    int A[100];
    int n, mid;
    int t, i;
    int x;
}

codeblock {
    n = 6;
    for i=1,n {
        A[i] = i;
    }

    A[2] = 4;
    A[5] = 6;

    for i=1,n {
        println A[i];
    }

}
