package CrazyEightStarterFixed;

/*
 * @author Gateway Instructors
 * @version 1.0
 */

import java.util.Scanner;

/**
 * The Class Start: Run this to start the game!
 */
public class Start {

   /**
    * The main method.
    *
    * @param args the arguments
    */
   public static void main(String[] args) {
      System.out.println("===================================");
      System.out.println("Welcome to Crazy Eights!");
      Scanner input = new Scanner(System.in);
      System.out.print("Please enter your name: ");
      String name = input.nextLine();
      System.out.println("===================================\n");

      Game crazyEight = new Game(name);
      crazyEight.playGame();

      input.close();
   }
}
