#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 30

int main()
{
    char group[SIZE],name[SIZE],surname[SIZE];
    double x1,x2,y,delta,bin,**A;
    int step,N;

    FILE* input=fopen("file.txt", "r");
    FILE* output=fopen("file_output.txt", "w");
    FILE* file_binary=fopen("file_binary.txt", "w+b");
    fscanf(input,"%lf %lf %d %lf", &x1, &x2, &step, &delta);
    fgets(surname,SIZE, input);
    fgets(group,SIZE, input);
    fgets(name,SIZE, input);
    if (step==0)
    {
        step=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(step-1);
    }
    fclose(input);

        fprintf(output,"\n******************************************");
        fprintf(output,"\n  N       X            F(X)           ");
        fprintf(output,"\n******************************************");
    fwrite(&step, sizeof(int), 1, file_binary);
    for(int i=0; i<step; i++)

    {
        y= -0.5*pow(x1-64,3)-3*pow(x1,2)+10;
        fprintf(output, "\n\t|%d|%.2lf\t|%.2lf\t|",i,x1,y);
        fwrite(&x1, sizeof(double), 1, file_binary);
        fwrite(&y, sizeof(double), 1, file_binary);
        x1+=delta;
    }
    fprintf(output,"\n%s %s %s", group, name, surname);
    fclose(output);
    fclose(file_binary);

    file_binary = fopen("file_binary.txt", "r+b");
    printf("\n|N|\t|X\t|\t|Y\t\t|");
    fread(&N, sizeof(int), 1, file_binary);

    A=(double**)malloc(3*sizeof(double*));
    for(int i=0; i<3; i++)
    {
        A[i]=(double*)malloc(N*sizeof(double));
    }

    for(int i=0; i<N; i++)
    {
        printf("\n|%d|", i);
        for(int j=1; j<3; j++)
        {
            fread(&bin, sizeof(double), 1, file_binary);
            A[j][i] = bin;
            printf("\t|%.2lf\t| ", A[j][i]);
        }
    }
    fclose(input);
    fclose(output);
    fclose(file_binary);
}

