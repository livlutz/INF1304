public class MyMath {
    public static int power(int a, int b){
        int res = 1;
        for(int i = 0; i < b; i++){
            res *= a;
        }
        return res;
    }
    public static int mult(int op1, int op2){
        int res = 0;
        for(int i = 0; i < op2; i++){
            res += op1;
        }
        return res;
    }
}