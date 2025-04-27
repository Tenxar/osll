#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

typedef struct process {
    int BT, AT, TAT, WT, PNO, PID;
    char name[10];
} process;

typedef struct RQ {
    process pr[MAX];
    int f, r;
} RQ;

void get_PCB(process[], int*);
void sort_AT(process[], int);
void disp_table(process[], int);
void RR(process[], int, int);
float cal_avgwt(process[], int);
float cal_avgtat(process[], int);
void menu();

int main() {
    int ch, TQ, n;
    process P[MAX];
    float avg_WT, avg_TAT;

    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &TQ);

    get_PCB(P, &n);

    do {
        menu();
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                RR(P, n, TQ);
                disp_table(P, n);
                avg_WT = cal_avgwt(P, n);
                avg_TAT = cal_avgtat(P, n);
                printf("\nAVERAGE WT  : %f", avg_WT);
                printf("\nAVERAGE TAT : %f", avg_TAT);
                break;
            case 2:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (ch != 2);

    return 0;
}

void menu() {
    printf("\n\t\t****MENU*****");
    printf("\n\t\t1. RR");
    printf("\n\t\t2. EXIT");
    printf("\n\t\tEnter Choice: ");
}

void get_PCB(process p[], int *n) {
    int i;
    printf("\nEnter total number of processes: ");
    scanf("%d", n);

    for (i = 0; i < *n; i++) {
        printf("\nEnter the following details for Process %d\n", i + 1);
        printf("Name: ");
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        p[i].PID = i; // Process ID
    }

    sort_AT(p, *n); // Sort processes based on arrival time
}

void sort_AT(process p[], int n) {
    int i, j;
    process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[j].AT < p[i].AT) {
                temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
}

float cal_avgwt(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].WT;
    }
    return avg / n;
}

float cal_avgtat(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].TAT;
    }
    return avg / n;
}

void check_arrival(RQ *r, process p[], int time, int n) {
    int i, j, flag = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= r->r; j++) {
            if (strcmp(p[i].name, r->pr[j].name) == 0)
                flag = 1;
            else
                break;
        }
        if (p[i].AT == time && flag == 0) {
            r->r = r->r + 1;
            r->pr[r->r] = p[i];
        }
        flag = 0;
    }
}

int get_first_process(process p[], int n) {
    int min = p[0].AT, in = 0;
    for (int j = 1; j < n; j++) {
        if (p[j].AT < min) {
            min = p[j].AT;
            in = j;
        }
    }
    return in;
}

void RR(process p[], int n, int tq) {
    int count = 0, time = 0;
    RQ r;
    r.f = r.r = -1;

    int start = get_first_process(p, n);
    r.pr[0] = p[start];
    r.f = r.r = 0;

    check_arrival(&r, p, time, n);

    while (r.f != -1) {
        for (count = 0; count < tq; count++) {
            r.pr[r.f].BT--;
            time++;

            if (r.pr[r.f].BT == 0) break;

            check_arrival(&r, p, time, n);
        }

        if (r.pr[r.f].BT != 0) {
            r.pr[r.r + 1] = r.pr[r.f];
            r.r++;
        } else {
            p[r.pr[r.f].PID].TAT = time - r.pr[r.f].AT;
            p[r.pr[r.f].PID].WT = p[r.pr[r.f].PID].TAT - p[r.pr[r.f].PID].BT;
        }

        if (r.f == r.r)
            r.f = r.r = -1;
        else
            r.f++;
    }
}

void disp_table(process p[], int n) {
    printf("\n\n P_NAME \t AT \t BT \t WT \t TAT");
    for (int i = 0; i < n; i++) {
        printf("\n %-10s \t %d \t %d \t %d \t %d", p[i].name, p[i].AT, p[i].BT, p[i].WT, p[i].TAT);
    }
}

