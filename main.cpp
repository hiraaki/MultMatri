//
// Created by mhi on 26/06/18.
//

#include <cstdlib>
#include <time.h>
#include <iostream>
#include <unistd.h>     // sleep
#include <time.h>       // clock_gettime

using  namespace std;
static double TimeSpecToSeconds(struct timespec* ts)
{
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
}
// Gera Matriz
void geraMatriz(double **M, int l, int c){
    int i, j;
    srand( (unsigned)time(NULL) ); // seed
    for(i = 0; i < l; i++){
        for(j = 0; j < c; j++){
            M[i][j] = (double)(rand() % 1000 + 1)/100; //(0~100 double)
        }
    }
    return;
}

void MulM1M2(double **M1, double **M2, double **R, int l, int c){
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            for(int M=0;M<l;M++){
                R[i][j]+= M1[i][M] *M2[M][j];
            }
        }
    }
}



double **create_space2D (int m, int n){
    //linha = m , coluna = n
    double **v;  /* ponteiro para a matriz */
    int   i;    /* variavel auxiliar      */
    if (m < 1 || n < 1) { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    /* aloca as linhas da matriz */
    v = (double **) calloc (m, sizeof(double *));
    if (v == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for ( i = 0; i < m; i++ ) {
        v[i] = (double *) calloc (n, sizeof(double));
        if (v[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (v); /* retorna o ponteiro para a matriz */
}

void MulM1M2T(double **M1, double **M2T, double **R, int l, int c){
    double  **MT =create_space2D(l,c);
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            MT[i][j]=M2T[j][i];
        }
    }

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            for(int M=0;M<l;M++){
                R[i][j]+= M1[i][M] *MT[j][M];
            }
        }
    }
}



int main(int argc, char *argv[]) {
    string linha=argv[1];
    string Coluna=argv[2];
    string op=argv[3];

    double **M1;
    double **M2;
    double **M3;
    struct timespec start, end;
    M1=create_space2D(atoi(linha.c_str()),atoi(Coluna.c_str()));
    M2=create_space2D(atoi(linha.c_str()),atoi(Coluna.c_str()));
    M3=create_space2D(atoi(linha.c_str()),atoi(Coluna.c_str()));



    geraMatriz(M1,atoi(linha.c_str()),atoi(Coluna.c_str()));
    geraMatriz(M2,atoi(linha.c_str()),atoi(Coluna.c_str()));

    if(op=="o"){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
        MulM1M2(M1,M2,M3,atoi(linha.c_str()),atoi(Coluna.c_str()));
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);

    }else if(op=="t"){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
        MulM1M2T(M1,M2,M3,atoi(linha.c_str()),atoi(Coluna.c_str()));
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
    } else if(op=="o|t"){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
        MulM1M2(M1,M2,M3,atoi(linha.c_str()),atoi(Coluna.c_str()));
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        printf("S: %lf, E: %lf\n", TimeSpecToSeconds(&start), TimeSpecToSeconds(&end));
        printf("Tempo: %lf segundos\n", TimeSpecToSeconds(&end) -
                                        TimeSpecToSeconds(&start));
        free(M3);
        M3=create_space2D(atoi(linha.c_str()),atoi(Coluna.c_str()));
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
        MulM1M2T(M1,M2,M3,atoi(linha.c_str()),atoi(Coluna.c_str()));
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        printf("S: %lf, E: %lf\n", TimeSpecToSeconds(&start), TimeSpecToSeconds(&end));
        printf("Tempo: %lf segundos\n", TimeSpecToSeconds(&end) -
                                        TimeSpecToSeconds(&start));
    }

    printf("S: %lf, E: %lf\n", TimeSpecToSeconds(&start), TimeSpecToSeconds(&end));
    printf("Tempo: %lf segundos\n", TimeSpecToSeconds(&end) -
                                    TimeSpecToSeconds(&start));

    free(M1);
    free(M2);
    free(M3);
//    for (int  i = 0;  i <   100; i++ ) {
//        for (int  j = 0;  j <   100; j++ ) {
//            cout<<M3[i][j]<<" ";
//        }
//        cout<<endl;
//    }

//    M1[0][0]=5;
//    M1[0][1]=4;
//    M1[1][0]=4;
//    M1[1][1]=4;
//
//    M2[0][0]=4;
//    M2[0][1]=4;
//    M2[1][0]=4;
//    M2[1][1]=4;
//
//    M3[0][0]=0;
//    M3[0][1]=0;
//    M3[1][0]=0;
//    M3[1][1]=0;
//
//
//    MulM1M2T(M1,M2,M3,2,2);
//    for (int  i = 0;  i <   2; i++ ) {
//        for (int  j = 0;  j <   2; j++ ) {
//            cout<<M3[i][j]<<" ";
//        }
//        cout<<endl;
//    }

    return 0;
}
