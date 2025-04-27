#include <stdio.h>
int main()
{

// P0, P1, P2, P3, P4 are the Process names here

int n, m, i, j, k;
n = 5; // Number of processes
m = 3; // Number of resources
int allocation[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix

{ 2, 0, 0 }, // P1
{ 3, 0, 2 }, // P2
{ 2, 1, 1 }, // P3
{ 0, 0, 2 } }; // P4

int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix

{ 3, 2, 2 }, // P1
{ 9, 0, 2 }, // P2
{ 2, 2, 2 }, // P3
{ 4, 3, 3 } }; // P4

int available[3] = { 3, 3, 2 }; // Available Resources

int finish[n], safe[n], ind = 0;
for (k = 0; k < n; k++) {
finish[k] = 0;

}
int need[n][m];
for (i = 0; i < n; i++) {

for (j = 0; j < m; j++)

need[i][j] = max[i][j] - allocation[i][j];

}

int y = 0;

for (k = 0; k < 5; k++) {

for (i = 0; i < n; i++) {
if (finish[i] == 0) {
int flag = 0;
for (j = 0; j < m; j++) {

if (need[i][j] > available[j]){

flag = 1;
break;

}

}

if (flag == 0) {

safe[ind++] = i;
for (y = 0; y < m; y++)
available[y] += allocation[i][y];
finish[i] = 1;
}
}
}

}

printf("SAFE Sequence is \n");
for (i = 0; i < n - 1; i++)

printf(" P%d ->", safe[i]);

printf(" P%d", safe[n - 1]);

return (0);

}
