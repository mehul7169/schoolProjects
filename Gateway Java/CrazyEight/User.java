package CrazyEightStarterFixed;

/*
 * @author Gateway Instructors
 * @version 1.0
 */

import java.util.Scanner;

/**
 * This class represents a human player (user) in a game of crazy eights.
 */
public class User extends Player {

   /**
    * To read user's input from keyboard.
    */
   private Scanner input;

   /**
    * Instantiates a human player with an empty hand.
    *
    * @param theName the name of the player
    */
   public User(String theName) {
      super(theName);
      input = new Scanner(System.in);
   }

   /**
    * Allow the user to select a Card from their hand and "play" it.
    * Make sure the think through all the steps involved to play 1
    * round of the game
    * @param crazyEight gives access to the "draw pile".
    * @param prev       the previously played card.
    * @return the card played by the user.
    */
   public Card play(Game crazyEight, Card prev) {  
      while (true) {
         System.out.println("Select a card from your hand");
         System.out.print(" or enter 0 to draw a new card: ");
         int number = input.nextInt();
         if (number == 0){
            Card card = crazyEight.draw();
            System.out.println("\n*** " + name + " draws " + card + "\n");
            hand.addCard(card);
            display();
         }
         else {
            Card card = hand.getCard(number - 1);
            if (cardMatches(card, prev)) {
               hand.popCard(number-1);
               return card;   
            }
            else {
               System.out.println("");
               System.out.println("--- This card is not a match!");
               System.out.println("");
            }
         }
         
         
      }
   }
}
