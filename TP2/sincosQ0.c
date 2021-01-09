#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tables.h"
#define epsilon 0.00000000000000000000000000000000000000000000000000000000001


void sincosQ0(double a, double *s, double *c)
{
    double x=kn[25],x1;
    double y=0;
    int d=1;
    int i=0;


    for(i=0; fabs(a-(d*at[i]))>epsilon && i<=57; i++)
    {

        if (a<0)
            d=-1;
        else if (a>=0)
            d=1;

        x1=x;
        x=x1-(d*y*pow(2,-i));
        y=y+(d*x1*pow(2,-i));
        a=a-(d*at[i]);

    }

    *c=x; *s=y;
}

double reduction (double a)
{
    for (   ;a>DEUXPI;    )
    {
        a=a-DEUXPI;
    }
    return a;
}

int quadrant ( double a)
{
    int q=3;
    if (a<PI)
    {
        if (a<PID2)
            q=0;
        else
            q=1;
    }
    else if (a<3*PID2)
            q=2;
    return q;
}

 void sincos(double a, double *s, double *c)
{
    double p=0;
    int q=quadrant(a);
    if (q==1)
    {
        sincosQ0(a-PID2,s,c);
        p=*c ; *c=-*s ;*s=p;
    }
    else if (q==2)
    {
        sincosQ0(a-PI,s,c);
        *s=-*s ; *c=-*c;
    }
    else if (q==3)
    {
        sincosQ0(a-3*PID2,s,c);
        p=*c ; *c=*s ;*s=-p;
    }
    else
        sincosQ0(a,s,c);
}
void Remplissage()
{
    FILE *fichier=NULL;
    double s=0,c,a;
    double i=0;

    fichier=fopen("ecart-sinus.txt","w");

    if (fichier !=NULL)
    {
    for (i=0; i<=360; i=i+0.5)
    {
        a=(i*PI)/180; /* conversion en degre*/
        sincos(a,&s,&c);
        fprintf(fichier, "%.1f %.17f\n",i,sin(a)-s);

    }
    }
    fclose(fichier);
}

int main()
{
    double sinus=0, cosinus=0, a=0, difs,difc;
    int q;
    printf("donner l'angle :\n");
    scanf("%lf", &a);
    printf("angle entre = %.16f\n", a);

    a=reduction(a);
    printf("angle reduit = %.16f\n", a);

    q=quadrant(a);
    printf("Vous travaillez dans le quadrant %d\n",q);

    sincos(a, &sinus, &cosinus);/*adresse de a car la fonction reduction recoit deux adresses */
    printf("cos(%.10f) = %.16f , sin(%.10f) =  %.16f \n", a,cosinus,a,sinus);

    difc=cos(a)-cosinus;
    difs=sin(a)-sinus;
    printf("Erreur cos = %.16f et Erreur sin = %.16f\n",difc,difs);

    Remplissage();
    /*system("wgnuplot ecart-sinus.txt -");*/

    return 0;
}





