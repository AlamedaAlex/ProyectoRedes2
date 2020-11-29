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
} SEMAPH;

//Zonas criticas para escribir dato.
char zona1[4], zona2[4], zona3[4], zona4[4], zona5[4], zona6[4];

void *productor1(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 10)
    {
        if (sem_trywait(&(ALL_SEM->sem_1_p)) == 0)
        {
            sprintf(zona1, "%s", "1111");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&(ALL_SEM->sem_1_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "1111");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "1111");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "1111");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "1111");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "1111");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
        }
    }
    pthread_exit(NULL);
}
void *productor2(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 10)
    {
        if (sem_trywait(&(ALL_SEM->sem_1_p)) == 0)
        {
            sprintf(zona1, "%s", "2222");
            printf("Estoy produciendo %s en zona1 %d\n", zona1, i);
            i++;
            sem_post(&(ALL_SEM->sem_1_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_p)) == 0)
        {
            sprintf(zona2, "%s", "2222");
            printf("Estoy produciendo %s en zona2 %d\n", zona2, i);
            i++;
            sem_post(&(ALL_SEM->sem_2_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_p)) == 0)
        {
            sprintf(zona3, "%s", "2222");
            printf("Estoy produciendo %s en zona3 %d\n", zona3, i);
            i++;
            sem_post(&(ALL_SEM->sem_3_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_p)) == 0)
        {
            sprintf(zona4, "%s", "2222");
            printf("Estoy produciendo %s en zona4 %d\n", zona4, i);
            i++;
            sem_post(&(ALL_SEM->sem_4_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_p)) == 0)
        {
            sprintf(zona5, "%s", "2222");
            printf("Estoy produciendo %s en zona5 %d\n", zona5, i);
            i++;
            sem_post(&(ALL_SEM->sem_5_c));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_p)) == 0)
        {
            sprintf(zona6, "%s", "2222");
            printf("Estoy produciendo %s en zona6 %d\n", zona6, i);
            i++;
            sem_post(&(ALL_SEM->sem_6_c));
        }
    }
    pthread_exit(NULL);
}

void *consumidor(void *args)
{
    SEMAPH *ALL_SEM = (SEMAPH *)args;
    int i = 0;
    while (i < 20)
    {
        if (sem_trywait(&(ALL_SEM->sem_1_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona1\n", zona1);
            i++;
            sem_post(&(ALL_SEM->sem_1_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_2_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona2\n", zona2);
            i++;
            sem_post(&(ALL_SEM->sem_2_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_3_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona3\n", zona3);
            i++;
            sem_post(&(ALL_SEM->sem_3_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_4_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona4\n", zona4);
            i++;
            sem_post(&(ALL_SEM->sem_4_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_5_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona5\n", zona5);
            i++;
            sem_post(&(ALL_SEM->sem_5_p));
        }
        else if (sem_trywait(&(ALL_SEM->sem_6_c)) == 0)
        {
            printf("Estoy consumiendo %s en zona6\n", zona6);
            i++;
            sem_post(&(ALL_SEM->sem_6_p));
        }
        else
            continue;
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    //Hilos que actuaran como los productores y consumidores.
    pthread_t productor_1, productor_2, productor_3, productor_4;
    pthread_t consumidor_1, consumidor_2, consumidor_3;
    FILE *archivo_1 = fopen("1111.txt", "w");
    FILE *archivo_2 = fopen("2222.txt", "w");
    FILE *archivo_3 = fopen("3333.txt", "w");
    FILE *archivo_4 = fopen("4444.txt", "w");
    SEMAPH sems;
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
    if (0 != pthread_create(&productor_1, NULL, productor1, &sems))
        return -1;
    if (0 != pthread_create(&productor_2, NULL, productor2, &sems))
        return -1;
    if (0 != pthread_create(&consumidor_1, NULL, consumidor, &sems))
        return -1;

    pthread_join(productor_1, NULL);
    pthread_join(productor_2, NULL);
    pthread_join(consumidor_1, NULL);
    return 0;
}
