// int accum = 0;

// int sum(int x, int y) {
//     int t = x + y;
//     accum += t;
//     return t;
// }

// struct aa {
//     int * a;
//     struct {
//         int x;
//         int y;
//     }s;
//     struct aa* next;
// };


// void sp_init(struct aa * a) {
//     //a->a = &s->x;
//     // a->a = ;
//     a->next = a;
// }
#define M 10000
#define N 100 

// int rowsum(int arry[M][N], int m, int n) {
//     int sum = 0;
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             sum += arry[i][j];
//         }
//     }
// }
int cowsum(int arry[M][N], int m, int n) {
    int sum = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum += arry[j][i];
        }
    }
}


#define REPEAT 10000
int main() {
    //printf("size of aa %d\n", sizeof(struct aa));
    int arry[M][N];
    int ret = 0;
    for(int i = 0; i < REPEAT;i++) {
        ret = cowsum(arry, M, N);
    }

    //return sum(1, 2);
}
