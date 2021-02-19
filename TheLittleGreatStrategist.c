#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct GrafMetrou
{
    int N; //nr statii
    int M; //nr drumuri
    int **matrice_adiacenta_subteran; //un singur astfel de graf.
};
typedef struct GrafMetrou G1;
struct GrafClienti
{
    int NrClienti;
    int NrStrazi;
    int **matrice_adiacenta_strazi; //unul pentru fiecare statie.
};
typedef struct GrafClienti G2;
struct persoana
{
    char *NumePersoana;
    int DistantaStatie;
    int Datorie;
};
typedef struct persoana Client;
struct statie
{
    char *Nume;
    int ComenziLivrate;
    int NumarClienti;
    Client *client;
};
typedef struct statie Statie;
int AsociereValoareint(char *v)
{
    int i,x=0,k=1;
    for(i=1;i<strlen(v);i++)
    {
        if((v[strlen(v)-i]<='9')&&(v[strlen(v)-i]>='0')) x=x+k*(v[strlen(v)-i]-'0');
        else return x;
        k=k*10;
    }
    return k;
}
void AfisareGraf2(G2 g)
{
    int i,j;
    for(i=0;i<g.NrClienti;i++)
    {
        for(j=0;j<g.NrClienti;j++)
        {
            printf(" %d ",g.matrice_adiacenta_strazi[i][j]);
        }
        printf("\n");
    }
}
void AfisareGraf1(G1 *g)
{
    int i,j;
    for(i=0;i<g->N;i++)
    {
        for(j=0;j<g->N;j++)
        {
            printf(" %d ",g->matrice_adiacenta_subteran[i][j]);
        }
        printf("\n");
    }
}
void conexiune(G2 g,int x,int y,FILE *f)
{
    if((x>g.NrClienti)||(y>g.NrClienti)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    if(g.matrice_adiacenta_strazi[x-1][y-1]) fprintf(f,"OK ");
    else fprintf(f,"NO ");
}
void blocaj_tunel(G1 *g,int x,int y)
{
    if((x>g->N)||(y>g->N)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g->matrice_adiacenta_subteran[x-1][y-1]=999;
    g->matrice_adiacenta_subteran[y-1][x-1]=999;
}
void blocaj_strada(G2 g,int x,int y)
{
    if((x>g.NrClienti)||(y>g.NrClienti)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g.matrice_adiacenta_strazi[x-1][y-1]=999;
    g.matrice_adiacenta_strazi[y-1][x-1]=999;
}
void sterge_ruta(G1 *g,int x,int y)
{
    if((x>g->N)||(y>g->N)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g->matrice_adiacenta_subteran[x-1][y-1]=0;
    g->matrice_adiacenta_subteran[y-1][x-1]=0;
}
void sterge_strada(G2 g,int x,int y)
{
    if((x>g.NrClienti)||(y>g.NrClienti)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g.matrice_adiacenta_strazi[x-1][y-1]=0;
    g.matrice_adiacenta_strazi[y-1][x-1]=0;
}
void adauga_ruta(G1 *g,int x,int y,int z)
{
    if((x>g->N)||(y>g->N)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g->matrice_adiacenta_subteran[x-1][y-1]=z;
    g->matrice_adiacenta_subteran[y-1][x-1]=z;
    g->M++;
}
void adauga_strada(G2 g,int x,int y,int z)
{
    if((x>g.NrClienti)||(y>g.NrClienti)||(x<=0)||(y<=0)) printf(" Cerere invalida ! ");
    g.matrice_adiacenta_strazi[x-1][y-1]=z;
    g.matrice_adiacenta_strazi[y-1][x-1]=z;
    g.NrStrazi++;
}
void legatura(G1 *g,int x,FILE *f)
{
    int i,ok=0;
    for(i=0;i<g->N;i++)
    {
        if(g->matrice_adiacenta_subteran[x-1][i]!=0)
        {
            ok=1;
            fprintf(f,"Statie%d ", i+1);
        }
    }
    if(ok==0) printf("\n");
}
int GasireMinim(int *dist,int *sps,int n)
{
    int i,poz,min=999;
    for(i=0;i<n;i++)
    {
        if((sps[i]==0)&&(dist[i]<=min))
        {
            min=dist[i];
            poz=i;
        }
    }
    return poz;
}
void AfisareCaleG2(Client *c,int *parinte,int x,FILE *f)
{
    if(parinte[x]==-1)
    {
        fprintf(f,"%s ",c[x].NumePersoana);
        return;
    }
    AfisareCaleG2(c,parinte,parinte[x],f);
    fprintf(f,"%s ",c[x].NumePersoana);
}
void AfisareCaleG1(Statie *s,int *parinte,int x,FILE *f)
{
    if(parinte[x]==-1)
    {
        fprintf(f,"%s ",s[x].Nume);
        return;
    }
    AfisareCaleG1(s,parinte,parinte[x],f);
    fprintf(f,"%s ",s[x].Nume);
}
void DijkstraG2(Client *c,G2 g, int src,int src2,FILE *f)
{
     int i,count,v,u;
     int *dist,*sps;
     int *parinte;
     dist=malloc(sizeof(int)*g.NrClienti);
     sps=malloc(sizeof(int)*g.NrClienti);
     parinte=malloc(sizeof(int)*g.NrClienti);
     for (i=0;i<g.NrClienti;i++)
     {
        parinte[i]=-1;
        dist[i]=999;
        sps[i]=0;
     }
     dist[src]=0;
     for (count=0;count<g.NrClienti-1;count++)
     {
       u=GasireMinim(dist,sps,g.NrClienti);
       sps[u]=1;
       for (v=0;v<g.NrClienti;v++)
       {
            if ((!sps[v]) && (g.matrice_adiacenta_strazi[u][v]) && (dist[u]!=999) && (dist[u]+g.matrice_adiacenta_strazi[u][v]<dist[v]))
            {
                dist[v] = dist[u] + g.matrice_adiacenta_strazi[u][v];
                parinte[v]=u;
            }
       }
     }
    AfisareCaleG2(c,parinte,src2,f);
}
void DijkstraG1(Statie *s,G1 *g, int src,int src2,FILE *f)
{
     int i,count,v,u;
     int *dist,*sps,*parinte;
     parinte=malloc(sizeof(int)*g->N);
     dist=malloc(sizeof(int)*g->N);
     sps=malloc(sizeof(int)*g->N);
     for (i=0;i<g->N;i++)
     {
        parinte[i]=-1;
        dist[i]=999;
        sps[i]=0;
     }
     dist[src]=0;
     for (count=0;count<g->N-1;count++)
     {
       u=GasireMinim(dist,sps,g->N);
       sps[u]=1;
       for (v=0;v<g->N;v++)
       {
            if ((!sps[v]) && (g->matrice_adiacenta_subteran[u][v]) && (dist[u]!=999) && (dist[u]+g->matrice_adiacenta_subteran[u][v]<dist[v]))
            {
                parinte[v]=u;
                dist[v] = dist[u] + g->matrice_adiacenta_subteran[u][v];
            }
       }
     }
     AfisareCaleG1(s,parinte,src2,f);
}
int minKey(int *key, int *mstSet,int n)
{
    int v;
    int min = 999, j;

    for ( v = 0; v < n; v++)
    if (mstSet[v] == 0 && key[v] < min)
    {
        min = key[v];
        j = v;
    }
    return j;
}
void printMST(int *parinte, int n, G2 g)
{
    int i,x=0;
    for ( i = 1; i < g.NrClienti; i++)
    {
        x=x+g.matrice_adiacenta_strazi[i][parinte[i]];
    }

    printf("%d", x);
}
void primMST(G2 g,int src)
{
    int i,count,v,u;
    int *parinte,*key,*mstSet;
    parinte=malloc(sizeof(int)*g.NrClienti);
    key=malloc(sizeof(int)*g.NrClienti);
    mstSet=malloc(sizeof(int)*g.NrClienti);
    for ( i = 0; i < g.NrClienti; i++)
    {
        parinte[i]=-1;
        key[i] = 999;
        mstSet[i] = 0;
    }
    key[src] = 0;
    for ( count = 0; count < g.NrClienti-1; count++)
    {
        u = minKey(key, mstSet,g.NrClienti);
        mstSet[u] = 1;
        for ( v = 0; v < g.NrClienti; v++)
        {
            if (g.matrice_adiacenta_strazi[u][v] && mstSet[v] == 0 && g.matrice_adiacenta_strazi[u][v] < key[v] && key[u]!=999)
            {
                parinte[v] = u, key[v] = g.matrice_adiacenta_strazi[u][v];
            }
        }
    }
    printMST(parinte, g.NrClienti, g);
}
void CitireDate(G1 **Harta_Metrou,G2 **Harta_Client,Statie **s,FILE *f)
{
    int i,j,k,n,distanta;
    int x,y;
    char *v;
    fscanf(f,"%d",&n);
    (*s)=malloc(sizeof(Statie)*n);
    (*Harta_Client)=malloc(sizeof(G2)*n);
    for(i=0;i<n;i++)
    {
        (*s)[i].Nume=malloc(sizeof(char)*15);
        fscanf(f,"%s",(*s)[i].Nume);
        fscanf(f,"%d",&(*s)[i].NumarClienti);
        (*s)[i].ComenziLivrate=0;
        (*s)[i].client=malloc(sizeof(Client)*((*s)[i].NumarClienti));
        for(j=0;j<(*s)[i].NumarClienti;j++)
        {
            (*s)[i].client[j].NumePersoana=malloc(sizeof(char)*25);
            fscanf(f,"%s",(*s)[i].client[j].NumePersoana);
            fscanf(f,"%d",&(*s)[i].client[j].DistantaStatie);
            fscanf(f,"%d",&(*s)[i].client[j].Datorie);
        }
        (*Harta_Client)[i].NrClienti=(*s)[i].NumarClienti;
        fscanf(f,"%d",&(*Harta_Client)[i].NrStrazi);
        (*Harta_Client)[i].matrice_adiacenta_strazi=(int**)malloc(sizeof(int*)*((*Harta_Client)[i].NrClienti));
        for(k=0;k<(*Harta_Client)[i].NrClienti;k++)
        {
            (*Harta_Client)[i].matrice_adiacenta_strazi[k]=(int*)calloc((*Harta_Client)[i].NrClienti,sizeof(int));
        }
        v=malloc(sizeof(char)*30);
        for(k=0;k<(*Harta_Client)[i].NrStrazi;k++)
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            fscanf(f,"%d",&distanta);
           (*Harta_Client)[i].matrice_adiacenta_strazi[x-1][y-1]=distanta;
           (*Harta_Client)[i].matrice_adiacenta_strazi[y-1][x-1]=distanta;
        }

    }
    (*Harta_Metrou)=malloc(sizeof(G1));
    (*Harta_Metrou)->N=n;
    fscanf(f,"%d",&(*Harta_Metrou)->M);
    (*Harta_Metrou)->matrice_adiacenta_subteran=(int**)malloc(sizeof(int*)*((*Harta_Metrou)->N));
    for(k=0;k<(*Harta_Metrou)->N;k++)
    {
        (*Harta_Metrou)->matrice_adiacenta_subteran[k]=(int*)calloc((*Harta_Metrou)->N,sizeof(int));
    }
    for(k=0;k<(*Harta_Metrou)->M;k++)
    {
        fscanf(f,"%s",v);
        x=AsociereValoareint(v);
        fscanf(f,"%s",v);
        y=AsociereValoareint(v);
        fscanf(f,"%d",&distanta);
        (*Harta_Metrou)->matrice_adiacenta_subteran[x-1][y-1]=distanta;
        (*Harta_Metrou)->matrice_adiacenta_subteran[y-1][x-1]=distanta;
    }
}
void comanda_statie(Statie *s,int x,int n,FILE *f)
{
    int i,j,tg=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<s[i].NumarClienti;j++)
        {
            tg=tg+s[i].client[j].Datorie;
        }
        if(tg>=x)
        {
            fprintf(f,"%s ", s[i].Nume);
        }
        tg=0;
    }
}
void exec(G1 *Harta_Metrou,G2 *Harta_Client,Statie *s,FILE *f,FILE *g)
{
    char *v;
    int n,i,x,y,z,p,ok=0;
    v=malloc(sizeof(char)*50);
    fscanf(f,"%d",&n);
    for(i=0;i<n;i++)
    {
        fscanf(f,"%s",v);
        if(!strcmp(v,"conexiune"))
        {
            if(ok!=0)
            {
                fprintf(g,"\n");
            }
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            z=v[6]-'0';
            conexiune(Harta_Client[z-1],x,y,g);
            ok=1;
        }
        else if(!strcmp(v,"legatura"))
        {
            if(ok!=0)
            {
                fprintf(g,"\n");
            }
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            legatura(Harta_Metrou,x,g);
            ok=1;
        }
        else if(!strcmp(v,"blocaj_tunel"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            blocaj_tunel(Harta_Metrou,x,y);
        }
        else if(!strcmp(v,"blocaj_strada"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            z=v[6]-'0';
            blocaj_strada(Harta_Client[z-1],x,y);
        }
        else if(!strcmp(v,"adauga_ruta"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            fscanf(f,"%d",&z);
            adauga_ruta(Harta_Metrou,x,y,z);
            Harta_Metrou->M=Harta_Metrou->M+1;
        }
        else if(!strcmp(v,"sterge_ruta"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            sterge_ruta(Harta_Metrou,x,y);
            Harta_Metrou->M=Harta_Metrou->M-1;
        }
        else if(!strcmp(v,"sterge_strada"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            z=v[6]-'0';
            sterge_strada(Harta_Client[z-1],x,y);
            Harta_Client[z-1].NrStrazi=Harta_Client[z-1].NrStrazi-1;
        }
        else if(!strcmp(v,"adauga_strada"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            fscanf(f,"%d",&p);
            z=v[6]-'0';
            adauga_strada(Harta_Client[z-1],x,y,p);
            Harta_Client[z-1].NrStrazi=Harta_Client[z-1].NrStrazi+1;
        }
        else if(!strcmp(v,"drum_strada"))
        {
            if(ok!=0)
            {
                fprintf(g,"\n");
            }
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            z=v[6]-'0';
            DijkstraG2(s[z-1].client,Harta_Client[z-1],x-1,y-1,g);
            ok=1;
        }
        else if(!strcmp(v,"drum_metrou"))
        {
            if(ok!=0)
            {
                fprintf(g,"\n");
            }
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            fscanf(f,"%s",v);
            y=AsociereValoareint(v);
            DijkstraG1(s,Harta_Metrou,x-1,y-1,g);
            ok=1;
        }
        /*else if(!stcmp(v,"timp_statie"))
        {
            fscanf(f,"%s",v);
            x=AsociereValoareint(v);
            primMST(Harta_Client[x],s[x].client);
        }      */
        else if(!strcmp(v,"comanda_statie"))
        {
            if(i!=0)
            {
                fprintf(g,"\n");
            }
            fscanf(f,"%d",&x);
            comanda_statie(s,x,Harta_Metrou->N,g);
            ok=1;
        }
    }
}
int main (int argc,char* argv[])
{
    G1 *Harta_Metrou;
    G2 *Harta_Client;
    Statie *s;
    FILE *f,*g;
    f=fopen(argv[1],"rt");
    g=fopen(argv[2],"wt");
    CitireDate(&Harta_Metrou,&Harta_Client,&s,f);
    exec(Harta_Metrou,Harta_Client,s,f,g);
    fclose(f);
    fclose(g);
}

