


int size = 896;

void matric_trans1(int src[size][size], int dest[size][size], int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            dest[j][i] = src[i][j];
        }
    }
}

void matric_trans2(int src[size][size], int dest[size][size], int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            dest[i][j] = src[j][i];
        }
    }
}
void matric_trans3(int src[size][size], int dest[size][size], int M) {
    int blocksize = 64;
    for(int i = 0; i < size;  i += blocksize) {
        for(int j = 0; j < size; j+= blocksize ) {
            for(int k = 0; k < blocksize; k++) {
                for(int m = 0; m < blocksize; m+=4) {
                    dest[i + k][j+m] = src[j+m][i+k];
                    dest[i + k][j+m+1] = src[j+m+1][i+k];
                    dest[i + k][j+m+2] = src[j+m+2][i+k];
                    dest[i + k][j+m+3] = src[j+m+3][i+k];
                }
            }
        }
    }
}


int main() {
    int src[size][size];
    int desc[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            src[i][j] = 10*i + j;
            desc[i][j] = 0;
        }
    }
    for(int i = 0; i < 10000; i++) {
        matric_trans3(src, desc, size);
    }

}