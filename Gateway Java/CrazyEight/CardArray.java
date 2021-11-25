package CrazyEightStarterFixed;

/**
 * This abstract class encapsulates an array of playing cards.
 */
public abstract class CardArray {

   /**
    * The cards.
    */
   protected Card[] cards;
   
   /**The index Filled up to.*/
   protected int numFilled;

   /**
    * Constructs an empty array of type Card.
    */
   public CardArray() {
      this.cards = new Card[52];
      this.numFilled = 0;
   }

   /**
    * Adds the card to array cards.
    *
    * @param card the card
    */
   public void addCard(Card card) {
      cards[numFilled] = card;
      numFilled++;
   }

   /**
    * This method has three jobs.
    * 1. It needs to get the last card.
    * 2. It then has to slide over everything to the right of the card
    * 3. It then returns the card that got moved over.
    * @return the last card in array cards
    */
   public Card popCard() {
      Card indexCard = cards[numFilled - 1];
      cards[numFilled - 1] = null;
      numFilled--;
      return indexCard;
   }

   /**
    * Size.
    *
    * @return the number of cards in the array cards.
    */
   public int size() {
      return this.numFilled;
   }

   /**
    * Empty.
    *
    * @return true, if the array of cards is empty;
    * false, otherwise.
    */
   public boolean empty() {
      return this.numFilled == 0;
   }

}
