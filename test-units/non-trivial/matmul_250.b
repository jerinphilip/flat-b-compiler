declblock {
    int A[62500], B[62500], C[62500];
    int i, j, k, n;
    int a, b, c;
}

codeblock {
    n = 250 - 1;
    for i=0, n {
        for j=0, n {
            if ( i == j ) {
                a = i*n + j;
                A[a] = 1;
            }
            else {
                a = i*n + j;
                A[a] = 0;
            }
        }
    }

    for i=0, n {
        for j=0, n {
            if ( i == j ) {
                a = i*n + j;
                B[a] = 1;
            }
            else {
                a = i*n + j;
                B[a] = 0;
            }
        }
    }

    for i=0, n {
        for j=0, n {
            for k=0, n {
                a = i*n + k;
                b = k*n + j;
                c = i*n + j;
                C[c] = C[c] + A[a]*B[b];
            }
        }
    }

    println "A:";

    for i=0, n {
        for j=0, n {
            a = i*n + j;
            print A[a], " ";
        }
        println "";
    }

    println "---";
    println "B:";

    for i=0, n {
        for j=0, n {
            a = i*n + j;
            print B[a], " ";
        }
        println "";
    }

    println "---";
    println "AB = C:";

    for i=0, n {
        for j=0, n {
            a = i*n + j;
            print C[a], " ";
        }
        println "";
    }

    println "---";
    
}
