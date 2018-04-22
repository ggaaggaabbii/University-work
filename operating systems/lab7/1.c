//the parent sends 2 ints to the child, the child adds them and sends back 
//the result

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int p2c[2],c2p[2];
    pipe(p2c);
    pipe(c2p);

    if (fork() == 0) {
        close(p2c[1]);
        close(c2p[0]);
        
        int x[2], s;
        
        read(p2c[0], x, 2 * sizeof(int));
        s = x[0] + x[1];
        write(c2p[1], &s, sizeof(int));
        
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    } else {
        close(p2c[0]);
        close(c2p[1]);
    
        int a = 2, b = 3;
        
        write(p2c[1], &a, sizeof(int));
        write(p2c[1], &b, sizeof(int));

        int s;        
        read(c2p[0], &s, sizeof(int));
        printf("%d\n", s);

        close(p2c[1]);
        close(c2p[0]);
        wait(0);
    }
    
    return 0;
}

