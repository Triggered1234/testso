/* adrian.enache03@e-uvt.ro

Scrieti un program C care va indeplini urmatoarele cerinte, folosind apeluri de
sistem pentru lucrul cu procese si pipe-uri:

a) va creea o structura de procese ca cea de mai jos (parent este procesul original main):
                                                                  (4 puncte)
| parent (main) |
        |
        +----------| child1 |
        |
        +----------| child2 |
        |
        \----------| child3 |
                       |
                       \-------| grandchild1 |

b) fiecare proces va afisa PID-ul parintelui sau la STDOUT.           (2 puncte)

c) fiecare proces isi va termina executia doar dupa ce toate procesele sale copil 
vor fi incheiat executia lor.                                         (2 puncte)

d) va crea un pipe intre child3 si grandchild1. Procesul child3 va citi din
pipe, iar grandchild1 va redirectiona STDOUT catre pipe.
Ambele procese vor inchide capetele nefolosite ale pipe-ului.    (1.5 puncte)

e) procesul grandchild1 va executa comanda `pwd -L' fara a crea
un proces nou.                                                      (2.5 puncte)

Programul va verifica succesul apelurilor de sistem. In caz contrar, va afisa 
un mesaj de eroare la STDERR si va opri executia.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t child1, child2, child3, grandchild1;
    int pipe_fd[2];

    // a) Creare structura de procese
    printf("Parent (main) PID: %d\n", getpid());

    if ((child1 = fork()) == 0) {
        printf("Child1 PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL); // Wait for child1 to complete
        if ((child2 = fork()) == 0) {
            printf("Child2 PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL); // Wait for child2 to complete
            if ((child3 = fork()) == 0) {
                printf("Child3 PID: %d, Parent PID: %d\n", getpid(), getppid());

                // d) Creare pipe intre child3 si grandchild1
                if (pipe(pipe_fd) == -1) {
                    perror("Error creating pipe");
                    exit(EXIT_FAILURE);
                }

                if ((grandchild1 = fork()) == 0) {
                    printf("Grandchild1 PID: %d, Parent PID: %d\n", getpid(), getppid());

                    // e) Executarea comenzii `pwd -L' fara a crea un proces nou
                    close(pipe_fd[1]); // Close write end of the pipe
                    dup2(pipe_fd[0], STDIN_FILENO);
                    close(pipe_fd[0]); // Close read end of the pipe

                    execlp("pwd", "pwd", "-L", (char *)NULL);
                    perror("Error executing pwd");
                    exit(EXIT_FAILURE);
                } else {
                    close(pipe_fd[0]); // Close read end of the pipe
                    dup2(pipe_fd[1], STDOUT_FILENO);
                    close(pipe_fd[1]); // Close write end of the pipe
                    wait(NULL); // Wait for grandchild1 to complete
                }

                // c) Child3 se termina doar dupa ce grandchild1 s-a incheiat
                exit(EXIT_SUCCESS);
            } else {
                wait(NULL); // Wait for child3 to complete
            }
        }
    }

    return 0;
}
