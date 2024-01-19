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

int main(int argc, char *argv[]) {

    return 0;
}
