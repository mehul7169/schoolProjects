package CrazyEightStarterFixed;

/*
 * @author Gateway Instructors
 * @version 1.0
 */


/**
 * This class represents a pile: a deck of cards that acts
 * as either Waste or Stock
 * <p>
 * Stock: a pile of cards, face down, to create a draw pile.
 * Waste: a pile of discarded cards.
 */
public class Pile extends Deck {

   /**
    * The label.
    */
   private String label;

   /**
    * Instantiates a new and empty pile!
    *
    * @param theLabel the label
    */
   public Pile(String theLabel) {
      this.cards = new Card[52];
      this.numFilled = 0;
      this.label = theLabel;
   }

   /**
    * Last: Returns (but not remove) the last card.
    *
    * @return the last card in the pile.
    */
   public Card last() {
      return cards[numFilled - 1];
   }


   /* Returns a string representation of the Pile.
    * Print in reverse order: last card is displayed first.
    */
   @Override
   public String toString() {
      if (this.numFilled == 0) {
         return label + " is empty.";
      }
      String output = label + ": [";
      for (int i = this.numFilled - 1; i > 0; i--) {
         output += cards[i].toString() + ", ";
      }
      output += cards[0].toString() + "]";
      return output;
   }
}
