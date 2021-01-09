#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double at(int i)
{
  return(atan(pow(2,-i)));
}

double kn(int n)
{
    double ki=0,kn=1;
    int i;
    for (i=0;i<n;i++)
    {
        ki=1/sqrt(1+pow(2,-2*i));
        kn *= ki;
    }
  return kn;
}

int main(int argc, char* argv[])
{
  int n,i;

  FILE *Tables=NULL;
  Tables=fopen("Tables.h","w");

  if (Tables != NULL)
  {
    fprintf(Tables," /* table des atan(2^-i), i dans [0:57] */ \ndouble at[] =\n{" )  ;
    for (i=0;i<=56;i++) /*expr on remarque que at[i]=0 apres i=57*/
    {
      fprintf(Tables,"%.16f, /* %d */\n",at(i),i);  /*.17 pour afficher 17 chiffres après la virgule*/
    }
      fprintf(Tables,"%.16f /* %d */\n",at(57),57); /* Pour ne pas mettre de virgule à la dernière ligne, il  faut sortir de la boucle et écrire la dernière ligne*/
      
      fprintf(Tables,"} ;\n\n/*table des kn, i dans [0:25] */\ndouble kn[] =\n{\n");
    for (n=1 ; n<=25;n++) /*Expérimentalement, on remarque qu'au dela de 26ieme valeur de Kn, Kn prend la même valeur*/
    {
        fprintf(Tables,"%.16f, /* %d */\n",kn(n),n-1);
    }
        fprintf(Tables,"%.16f /* %d */\n",kn(26),26-1);
     fprintf(Tables,"} ;\n #define PI 3.14159265358979312 \n #define DEUXPI 6.28318530717958623  /* 2*PI */ \n #define PID2 1.5707963267948656	/* PI/2 */ \n #define PID4 0.78539816339744828	/* PI/4 */ ");

  fclose(Tables);
  }
  return 0;
}
