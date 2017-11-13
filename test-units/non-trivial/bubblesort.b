declblock {
    int A[100];
    int i, j, t;
}

codeblock {
    for j = 0, 99 {
        A[j] = 100 - j;
        println A[j];
    }

    for i = 0, 99 {
        for j = i, 99 {
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

    for j = 0, 99 {
        println A[j];
    }
}
