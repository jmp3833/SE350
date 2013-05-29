/**
 * @author: Justin Peterson
 * @email: Jmp3833@rit.edu
 * FizzBuzz.java
 */

/**
 * Simple FizzBuzz programming problem
 * Divisible by 3 - Fizz
 * Divisible by 5 - Buzz
 * Divisible by 3 and 5 - FizzBuzz
 */
public class FizzBuzz {
 
 
 public static void fizzBuzz(){
  for( int x = 1; x < 101; x++){
   if (x % 15 == 0){
    System.out.println(("FizzBuzz"));
   }
   else if (x % 3 == 0){
    System.out.println(("Fizz"));
   }
   else if (x % 5 == 0){
    System.out.println(("Buzz"));
   }
   else{
    System.out.println(x);
   }
  }
 }
 
 public static void main(String[] args){
  fizzBuzz();
 }

}
