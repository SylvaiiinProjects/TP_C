#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#define Pi 3.14159265358979312
typedef double (*derivee) (double,double,double,void*);


double reduction(double angle)/* Pour rester dans le cerlce trigonometrique*/
{
  for ( ; angle>=360 ; )
  {angle=angle-360;}
 return angle ;
}

double deg2Rad(double angle) /* Pour convertir degres en radian*/
{
return(angle*Pi/180);
}

struct dataSim
{
  int flux; /* 0 pour le flux sinusoidal et 1 pour le flux indiciel */
  double m; /* masse de l'aile */
  double ro; /* mase volumique air */
  double S; /* surface de l'aile */
  double alpha0; /* angle d'incidence initial de l'aile */
  double k; /* raideur ressort equivalent  */
  double u0;
  double deltaU;
  double z0;
  double v0;
  double t;
  double u;
};

void initialiser(struct dataSim *data)
{
  data->m = 3;
  data->ro = 1.22;
  data->S = 0.3;
  data->alpha0 = deg2Rad(10);
  data->k = 980;
  data->u0 = 7.5;
  data->deltaU = 1.5;
  data->z0 = 0;
  data->v0 = 0;
  data->t = 0;
  data->u = 0;

  printf("choisir le type de flux : \n flux sinusoîdal = 0 , flus indiciel = 1 \n");
  scanf("%d",&((*data).flux));
}

double vent(double t,struct dataSim *params)
{
  int n; double u0=7.5 ,deltau=1.5;
  double w0=sqrt((*params).k/(*params).m);


  if ( (*params).flux == 0 )
  {
    if (t<=0)
    {return 0;}
    else
    {
    return(u0+deltau*sin(w0*t));
    }
  }
  else
  { if ((t<1) || (t>=4))
    {return 0 ; }
    else
    {return(deltau);}
  }
}


double coeffPortance(double angle )
{
  if ((reduction(angle)<=18) || (reduction(angle)>=342))
  {
    return 2*Pi*angle;}
  else
    return 0;
}

/* Calcul des deux fonctions derivees*/
double f(double z, double v, double t, void *params)
{
  return v;

}

double g(double z, double v, double t, void *params)
{
  struct dataSim *param1;
  param1 = params;
  double res;
  double angle_incidence;
  double u= vent(t,param1);
  angle_incidence= deg2Rad(param1->alpha0) - atan(v/u);
  res=coeffPortance ( angle_incidence );
  res = res * ( param1->ro );
  res = res *( param1->S );
  res = res * u;
  res = res * sqrt ( pow ( u, 2 ) + pow( v , 2 ) );
  res = res - z * (param1->k) / (param1->m) ;
  return ( res );
}

/* Resolution numerique du probleme avec la methode RK4*/
void rk4(double *z,double*v,double *t,double dt, derivee f, derivee g, void *params)
{
  double kz1,kz2,kz3,kz4,kv1,kv2,kv3,kv4;

  kz1= f((*z),(*v),(*t),params)*dt;
  kv1= g((*z),(*v),(*t),params)*dt;

  kz2= f((*z)+kz1/2,(*v)+kv1/2,(*t)+dt/2,params)*dt;
  kv2= g((*z)+kz1/2,(*v)+kv1/2,(*t)+dt/2,params)*dt;

  kz3= f((*z)+kz2/2,(*v)+kv2/2,(*t)+dt/2,params)*dt;
  kv3= g((*z)+kz2/2,(*v)+kv2/2,(*t)+dt/2,params)*dt;

  kz4= f((*z)+kz3/2,(*v)+kv3/2,(*t)+dt/2,params)*dt;
  kv4= g((*z)+kz3/2,(*v)+kv3/2,(*t)+dt/2,params)*dt;

  *z = *z +  ( kz1 + 2*kz2 + 2*kz3 + kz4 ) / 6;
  *v = *v +  ( kv1 + 2*kv2 + 2*kv3 + kv4 ) / 6;
  *t=*t+dt;
}


void Remplissage()
{
    struct dataSim data;
    double z=0, t=0, v=0, dt=0.006953;
    initialiser(&data);
    FILE *fichier=NULL;

    fichier=fopen("simulations.txt","w");

    if (fichier != NULL)
    {

        for (t=0; t<4; )
        {
            fprintf(fichier,"%lf ",t);
            rk4(&z,&v,&t,dt,f,g,&data);
            fprintf(fichier,"%lf\n",z);
        }
    }
    fclose(fichier);
}


int main (int argc, char *argv[])
{
    Remplissage();

    return 0;
}









