package CrazyEightStarterFixed;

/*
 * @author Gateway Instructors
 * @version 1.0
 */

/**
 * This class represents a hand: the cards held by one player.
 */
public class Hand extends CardArray {

   /**
    * Instantiates a new hand.
    */
   public Hand() {
      super();
   }

   /**
    * Pop card: removes and returns the card in Hand at
    * the given index.
    * <p>
    * Note: this method overloads popCard() in CardArray class.
    * </p>
    *
    * @param i the (zero-based) index of a card in Hand.
    * @return the card
    */
   public Card popCard(int i) {
      Card indexCard = cards[i];
      for (int j = i; j < numFilled - 1; ++j) {
         cards[j] = cards[j + 1]; 
      } 
      cards[numFilled - 1] = null;
      numFilled--;
      return indexCard; 
   }

   /**
    * Gets the card: returns (but does not remove) the card
    * in Hand at the given index.
    *
    * @param i the (zero-based) index of a card in Hand.
    * @return the card
    */
   public Card getCard(int i) {
      Card indexCard = cards[i];
      return indexCard; 
   }

   /* Returns a string representation of the Hand. */
   @Override
   public String toString() {
      if (this.numFilled == 0) {
         return "empty!";
      }
      String output = "";
      for (int i = 0; i < this.numFilled; i++) {
         output += "[" + Integer.toString(i + 1) + "]: " + cards[i] + "\n";
      }
      return output;
   }
}
