declblock{
    int x;
    int y;
    int s, t[10];
}

codeblock{
L2: x = 0;
    for x = 1, 100, 1 {
        t[x] = x;
    }

    for x = 1, 100{
        print t[x];
    }
}

