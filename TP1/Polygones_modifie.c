#include <math.h>
#include <stdio.h>

int  Points_Coordonnees( double pts[][3]) /* pts[] ou pts[100] fonctionne */
{

    int i, nbpts;

    printf("\nNombre de points du poylgone ? ");
    scanf("%i", &nbpts);

    i=0;
    while( i < nbpts)
    {
        printf("\n Point No %d >", i);
        scanf("%lf%lf%lf", &pts[i][0], &pts[i][1], &pts[i][2]) ;
        i=i+1;
    }
    return nbpts ;
}

int fermer_polygone( double pts[][3], int nbpts)
{
    pts[nbpts][0] = pts[0][0];
    pts[nbpts][1] = pts[0][1];
    pts[nbpts][2] = pts[0][2];
    return nbpts+1;

}

void Point_tester(double q[3])
{
    printf("\n Point a tester >");
    scanf("%lf%lf%lf", &q[0],&q[1],&q[2]);

}




int valeur_somme( int nbpts, double pts[][3], double q[3], double pvec[3], double v1[3],double v2[3])
{
    int i=0,  k, som=0.0;
    double x,y;
    while(i<nbpts-1)
    {
        k=0;
        while(k<3)
        {
            v1[k] = pts[i][k] - q[k] ;
            v2[k]= pts[i+1][k] - q[k];
            k=k+1;
        }

        pvec[0] = v1[1]*v2[2] + v1[2]*v2[1];
        pvec[1] = -(v1[0]*v2[2] - v1[2]*v2[0]);
        pvec[2] = v1[0]*v2[1] - v1[1]*v2[0];

        k=0;
        y=x=0.0;
        while(k<3)
        {
            y = y + pvec[k]*pvec[k];
            x = x + v1[k]*v2[k];
            k = k + 1;
        }

        som = som + atan2(sqrt(y),x);
        i = i + 1;
    }
    return som;
}

void Int_Ext(int som)
{
    if (fabs(som-6.283185307179586) < 1.0E-10)
        printf("Point interieur \n");
    else
        printf("Point exterieur \n");

}

int main ()
{   double pts[100][3], q[3], v1[3], v2[3], som, pvec[3], y,x ;
    int i,k, nbpts;

    nbpts = Points_Coordonnees(pts) ;

    if nbpts <= 100
        {
            nbpts = fermer_polygone(pts, nbpts) ;

            Point_tester(q);


            som= valeur_somme(nbpts, pts, q, pvec, v1,v2);

            Int_Ext(som);
        }
    else
    {
        printf("Le nombre de points du polygone doit �tre <= � 100!");
    }
    return 0;
}






