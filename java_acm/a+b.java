import java.util.*;
import java.io.*;
 
public class Main{
    public static void main(String[] args){
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        int a = cin.nextInt();
        int b = cin.nextInt();
        System.out.println(a+b);
        cin.close();
    }
}