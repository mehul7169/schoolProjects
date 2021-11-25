package CrazyEightStarterFixed;


/**
 * The Class Demo: Run this to see two player (computer) play crazy eights.
 */
public class Demo {

   /**
    * The main method.
    *
    * @param args the arguments
    */
   public static void main(String[] args) {
      System.out.println("===================================");
      System.out.println("Welcome to Crazy Eights!");
      System.out.println("===================================\n");

      Game crazyEight = new Game();
      crazyEight.playGame();
   }

}
