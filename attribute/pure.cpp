__attribute__ ((pure)) int my_square(int val){
    return val*val;
}

int my_square_no_pure(int val){
    return val*val;
}

int main(void){
   //my_square(3);
   my_square_no_pure(2);
}
