declblock {
    int x, q, nr, dr, r;
    int y;
}

codeblock {
    x = 1;
    while ( x < 100 ){
        dr = 15;
        q = x / dr;
        y = q * dr;
        r = x - y;
        if ( r == 0 ){
            println x, ":", "Fizzbuzz";
        }

        else {
            dr = 5;
            q = x / dr;
            y = q * dr;
            r = x - y;
            if ( r == 0 ){
                println x, ":", "Buzz";
            }
            else {
                dr = 3;
                q = x / dr;
                y = q * dr;
                r = x - y;
                if ( r == 0 ){
                    println x, ":", "Fizz";
                }
                
            }
            
        }


        x = x + 1;
    }
}
