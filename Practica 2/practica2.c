#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

typedef struct semaph
{
    //Semaforos necesarios para cubrir las secciones criticas.
    sem_t sem_1_p, sem_1_c, sem_2_p, sem_2_c, sem_3_p, sem_3_c;
    sem_t sem_4_p, sem_4_c, sem_5_p, sem_5_c, sem_6_p, sem_6_c;
    sem_t sem_a1, sem_a2, sem_a3, sem_a4;
    sem_t sem_aux_p, sem_aux_c;
} SEMAPH;

//Zonas criticas para escribir dato.
char zona1[4] = "", zona2[4] = "", zona3[4] = "", zona4[4] = "", zona5[4] = "", zona6[4] = "";

FILE *archivo_1, *archivo_2, *archivo_3, *archivo_4;

int producciones = 20;

void *productor1(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    int val;
    while (i < 10)
    {
        //sem_wait(&ALL_SEM->sem_aux_p);
        if (sem_trywait(&ALL_SEM->sem_1_p) == 0)
        {
            sprintf(zona1, "%s", "1111\0");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&ALL_SEM->sem_1_c);
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "1111\0");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "1111\0");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "1111\0");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "1111\0");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "1111\0");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
    }
    //sem_post(&ALL_SEM->sem_aux_c);
    pthread_exit(NULL);
}
void *productor2(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 10)
    {
        //sem_wait(&ALL_SEM->sem_aux_p);
        if (sem_trywait(&(ALL_SEM->sem_1_p)) == 0)
        {
            sprintf(zona1, "%s", "2222\0");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&(ALL_SEM->sem_1_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "2222\0");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "2222\0");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "2222\0");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "2222\0");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "2222\0");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
            //sem_post(&ALL_SEM->sem_aux_p);
        }
    }
    //sem_post(&ALL_SEM->sem_aux_c);
    pthread_exit(NULL);
}
void *productor3(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 10)
    {
        if (sem_trywait(&(ALL_SEM->sem_1_p)) == 0)
        {
            sprintf(zona1, "%s", "3333");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&(ALL_SEM->sem_1_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "3333");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "3333");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "3333");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "3333");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "3333");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
        }
    }
    //sem_post(&ALL_SEM->sem_aux_c);
    pthread_exit(NULL);
}
void *productor4(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 10)
    {
        if (sem_trywait(&(ALL_SEM->sem_1_p)) == 0)
        {
            sprintf(zona1, "%s", "4444");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&(ALL_SEM->sem_1_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "4444");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "4444");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "4444");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "4444");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "4444");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
        }
    }
    //sem_post(&ALL_SEM->sem_aux_c);
    pthread_exit(NULL);
}
void *consumidor(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (producciones > 1)
    {
        //sem_wait(&ALL_SEM->sem_aux_c);
        if (sem_trywait(&(ALL_SEM->sem_1_c)) == 0)
        {
            if (strcmp(zona1, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona1);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona1, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona1);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona1, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona1);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona1, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona1);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_1_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_c)) == 0)
        {
            if (strcmp(zona2, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona2);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona2, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona2);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona2, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona2);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona2, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona2);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_2_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_c)) == 0)
        {
            if (strcmp(zona3, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona3);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona3, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona3);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona3, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona3);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona3, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona3);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_3_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_c)) == 0)
        {
            if (strcmp(zona4, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona4);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona4, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona4);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona4, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona4);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona4, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona4);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_4_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_c)) == 0)
        {
            if (strcmp(zona5, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona5);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona5, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona5);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona5, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona5);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona5, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona5);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_5_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_c)) == 0)
        {
            if (strcmp(zona6, "1111") == 0)
            {
                sem_wait(&ALL_SEM->sem_a1);
                fprintf(archivo_1, "%s\n", zona6);
                sem_post(&ALL_SEM->sem_a1);
            }
            else if (strcmp(zona6, "2222") == 0)
            {
                sem_wait(&ALL_SEM->sem_a2);
                fprintf(archivo_2, "%s\n", zona6);
                sem_post(&ALL_SEM->sem_a2);
            }
            else if (strcmp(zona6, "3333") == 0)
            {
                sem_wait(&ALL_SEM->sem_a3);
                fprintf(archivo_3, "%s\n", zona6);
                sem_post(&ALL_SEM->sem_a3);
            }
            else if (strcmp(zona6, "4444") == 0)
            {
                sem_wait(&ALL_SEM->sem_a4);
                fprintf(archivo_4, "%s\n", zona6);
                sem_post(&ALL_SEM->sem_a4);
            }
            producciones--;
            sem_post(&(ALL_SEM->sem_6_p));
        }
        //sem_post(&ALL_SEM->sem_aux_c);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    //Hilos que actuaran como los productores y consumidores.
    pthread_t productor_1, productor_2, productor_3, productor_4;
    pthread_t consumidor_1, consumidor_2, consumidor_3;
    SEMAPH sems;
    archivo_1 = fopen("1111.txt", "w");
    archivo_2 = fopen("2222.txt", "w");
    archivo_3 = fopen("3333.txt", "w");
    archivo_4 = fopen("4444.txt", "w");

    sem_init(&(sems.sem_1_p), 0, 1);
    sem_init(&(sems.sem_2_p), 0, 1);
    sem_init(&(sems.sem_3_p), 0, 1);
    sem_init(&(sems.sem_4_p), 0, 1);
    sem_init(&(sems.sem_5_p), 0, 1);
    sem_init(&(sems.sem_6_p), 0, 1);

    sem_init(&(sems.sem_1_c), 0, 0);
    sem_init(&(sems.sem_2_c), 0, 0);
    sem_init(&(sems.sem_3_c), 0, 0);
    sem_init(&(sems.sem_4_c), 0, 0);
    sem_init(&(sems.sem_5_c), 0, 0);
    sem_init(&(sems.sem_6_c), 0, 0);

    sem_init(&sems.sem_a1, 0, 1);
    sem_init(&sems.sem_a2, 0, 1);
    sem_init(&sems.sem_a3, 0, 1);
    sem_init(&sems.sem_a4, 0, 1);
    sem_init(&sems.sem_aux_p, 0, 1);
    sem_init(&sems.sem_aux_c, 0, 1);

    if (0 != pthread_create(&productor_1, NULL, productor1, &sems))
        return -1;
    if (0 != pthread_create(&productor_2, NULL, productor2, &sems))
        return -1;
    /*  if (0 != pthread_create(&productor_3, NULL, productor3, &sems))
        return -1;
    if (0 != pthread_create(&productor_4, NULL, productor4, &sems))
        return -1; */
    if (0 != pthread_create(&consumidor_1, NULL, consumidor, &sems))
        return -1;
    if (0 != pthread_create(&consumidor_2, NULL, consumidor, &sems))
        return -1;
    if (0 != pthread_create(&consumidor_3, NULL, consumidor, &sems))
        return -1;

    pthread_join(productor_1, NULL);
    pthread_join(productor_2, NULL);
    /* pthread_join(productor_3, NULL);
    pthread_join(productor_4, NULL); */
    pthread_join(consumidor_1, NULL);
    pthread_join(consumidor_2, NULL);
    pthread_join(consumidor_3, NULL);
    return 0;
}
