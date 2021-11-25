package CrazyEightStarterFixed;

/**
 * This class represents a standard playing card.
 */
public class Card implements Comparable {
   /**
    * The Constant array of RANKS.
    */
   private static final String[] RANKS = {
      null, "Ace", "2", "3", "4", "5", "6", "7",
      "8", "9", "10", "Jack", "Queen", "King"};
   /**
    * The Constant array of SUITS.
    */
   private static final String[] SUITS = {
      "Clubs", "Diamonds", "Hearts", "Spades"};
   /**
    * A suit symbol on a card.
    */
   private final int suit;
   /**
    * The position of a card relative to others in the same suit.
    */
   private final int rank;


   /**
    * Instantiates a new card.
    *
    * @param theRank the rank
    * @param theSuit the suit
    */
   public Card(int theRank, int theSuit) {
      this.rank = theRank;
      this.suit = theSuit;
   }

   /**
    * Gets the rank.
    *
    * @return the rank
    */
   public int getRank() {
      return this.rank;
   }

   /**
    * Gets the suit.
    *
    * @return the suit
    */
   public int getSuit() {
      return this.suit;
   }

   /**
    * Compare this card to the <code>otherCard</code>.
    *
    * @param otherCard the other Card object.
    * @return -1, if this card comes before the given card;
    * 0, if the two cards are equal;
    * 1, if this card comes after the card.
    */
   @Override
   public int compareTo(Object otherCard) {
      Card that = (Card) otherCard;
      if (this.suit < that.suit) {
         return -1;
      }
      if (this.suit > that.suit) {
         return 1;
      }
      if (this.rank < that.rank) {
         return -1;
      }
      if (this.rank > that.rank) {
         return 1;
      }
      return 0;
   }

   /**
    * Check if this this is equal to the <code>otherCard</code>.
    *
    * @param otherCard the other Card object.
    * @return true, if the given card has the same
    * rank AND same suit; otherwise returns false.
    */
   public boolean equals(Object otherCard) {
      Card that = (Card) otherCard;
      return this.rank == that.rank
         && this.suit == that.suit;
   }

   /* Returns a string representation of the card.  */
   @Override
   public String toString() {
      return RANKS[this.rank] + " of " + SUITS[this.suit];
   }
}