int main(int argc, char const *argv[])
{
    const int SIZE = 100;
    int x;
    int a[SIZE];
    int i; 
    int found = 0;
    int temp = SIZE;
    while(found == 0){
        temp = temp/2;
        if(x == a[temp]){
            return a[temp];
            found ==1;
        }
        else if(x > a[temp]){
            temp +=(temp/2);
            if(x == a[temp]){
                return a[temp];
                found ==1;
            }
        }
        else if(x < a[temp]){
            temp = temp/2;
            if(x == a[temp]){
                return a[temp];
                found ==1;
            }
        }
    }
    return 0;
}
