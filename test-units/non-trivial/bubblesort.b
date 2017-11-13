declblock {
    int A[100];
    int i, j, t;
    int n;
}

codeblock {
    n = 100 - 1;
    for j = 0, n {
        A[j] = 100 - j;
        println A[j];
    }

    for i = 0, n {
        for j = i, n {
            print i, j,"=" ,A[i], A[j];
            if ( A[j] < A[i] ){
                t = A[j];
                A[j] = A[i];
                A[i] = t;
                print " Swapping";
            }
            println "";
        }
    }

    for j = 0, n {
        println A[j];
    }
}
