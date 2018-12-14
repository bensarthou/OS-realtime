#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

/*
On considère la fonction de signature : void incr(unsigned int nLoops, double* pCounter).
Cette fonction doit effectuer une boucle incrémentant de 1.0 la valeur du compteur pointée par
pCounter  elle doit effectuer cette boucle nLoops fois.

    Écrivez le code de cette fonction.

La signature standard du point d’entrée d’un programme est : int main(int argc, char* argv[]).
 Le paramètre argc indique le nombre de chaines de caractères de la ligne de commande ayant
 lancé l’exécution du programme ; le paramètre argv est le tableau de l’ensemble de ces chaines
 dans l’ordre où ils ont été tapés sur la ligne de commande, argv[0] étant le nom du programme,
 argv[1] son 1er paramètre, argv[2] son 2e paramètre, etc. Ici, la fonction main doit :

– déclarer une variable nLoops et l’initialiser avec la valeur numérique décimale de argv[1]‎ ;
– déclarer un compteur counter de type double et l’initialiser à 0.0 ;‎
– appeler la fonction incr sur ces deux variables ;
– imprimer à l’écran la valeur finale de counter. ‎

    Écrivez, compilez et exécutez le programme ainsi défini. Notez la valeur finale du compteur
    counter.

Renseignez-vous sur la fonction Posix clock_gettime exposée dans le cours.

    En utilisant clock_gettime, affichez à la fin du programme le temps d’exécution de la fonction
    incr ; ‎affichez ce temps en secondes sous la forme d’un nombre à virgule.‎
*/

void incr(unsigned int nLoops, double* pCounter)
{
    for(int i = 0; i<nLoops; i++)
    {
        *pCounter += 1.0;
    }
}


int main(int argc, char* argv[])
{

    unsigned int nLoops = atoi(argv[1]);
    double counter = 0.0;

    struct timespec debut, fin, duree;

    clock_gettime(CLOCK_REALTIME, &debut);
    // On mesure l'execution de la fonction
    incr(nLoops, &counter);

    clock_gettime(CLOCK_REALTIME, &fin);
    std::cout << "Valeur finale de pCounter:" << counter << std::endl;

    // Calcul de la différence de 2 instants
    duree.tv_sec = fin.tv_sec - debut.tv_sec;
    // Gestion du cas overflow des nanoseconds
    if (fin.tv_nsec < debut.tv_nsec)
    {
        duree.tv_sec -= 1;
        fin.tv_nsec += 1000000000;
    }

    duree.tv_nsec = fin.tv_nsec - debut.tv_nsec;

    printf("Measured duration is %d seconds and %d nanoseconds, equivalent to %f millisconds\n",
    duree.tv_sec, duree.tv_nsec, duree.tv_sec*1000. + duree.tv_nsec/1000000.);
}
