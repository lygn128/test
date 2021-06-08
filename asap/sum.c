int sum(int *arry, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += arry[i];
    }
    return s;
}