#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

//Time Inicio
struct timeval inicio, overall_start, overall_end;
int error, flag = 0;

int format(double a) {
    while(a >= 10) {
        a /= 10;
    }

    int res = (int)a;
    
    return res;
}

int main() {
    //Recebe PATH
    char PATH[256], arg[256];
    while(scanf("%s %s", PATH, arg) != EOF){
        //Flag e time
        if(flag == 0){
            gettimeofday(&overall_start, NULL);
            flag++;
        }
        gettimeofday(&inicio, NULL);
        
        //Cria fork
        int pid = fork();
        
        //Se for o filho
        if (pid==0) {
            execl(PATH, PATH, arg, NULL);  
            if (strcmp(strerror(errno), "Success") != 0){
                error = errno;
                printf("Erro: %s\n", strerror(error));
                exit(0);
            }
        }
        if (wait(NULL)) {
            struct timeval final;
            gettimeofday(&final, NULL);
            printf("Demorou %.1d.%.1d segundos, retornou %d\n", format(final.tv_sec - inicio.tv_sec), format(final.tv_usec - inicio.tv_usec), error);
        }
    }
    gettimeofday(&overall_end, NULL);

    printf("O tempo total foi de %.1d.%.1d segundos\n", format(overall_end.tv_sec - overall_start.tv_sec), format(overall_end.tv_usec - overall_start.tv_usec));
    exit(0);
}