
double mean(int length, int *arr){
    double mean;
    int i;
    for(i = 0; i < length; i++){
        mean += arr[i];
    }
    return mean/length;
}