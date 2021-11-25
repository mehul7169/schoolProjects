package CrazyEightStarterFixed;

/*
 * @author Gateway Instructors
 * @version 1.0
 */

/**
 * This class encapsulates a player in a game of crazy eights.
 */
public abstract class Player {

   /**
    * The name of the player.
    */
   protected String name;

   /**
    * The hand: the cards held by one player.
    */
   protected Hand hand;

   /**
    * Instantiates a new player with an empty hand.
    *
    * @param theName the name of the player
    */
   public Player(String theName) {
      this.name = theName;
      this.hand = new Hand();
   }

   /**
    * Card matches: two cards match if their rank or suit is the same.
    * <p>
    * Note: if card1's rank is 8, it is a Wild Card.
    * A wild card can match any other card
    * </p>
    *
    * @param card1 the card 1
    * @param card2 the card 2
    * @return true, if card1 matches card2
    */
   public static boolean cardMatches(Card card1, Card card2) {
      
      if (card1.getRank() == 8) {
         return true;
      }
      
      return (card1.getRank() == card2.getRank() 
         || card1.getSuit() == card2.getSuit());
   }

   /**
    * Gets the name.
    *
    * @return the name of the player.
    */
   public String getName() {
      return name;
   }

   /**
    * Gets the hand.
    *
    * @return the player's hand.
    */
   public Hand getHand() {
      return hand;
   }

   /**
    * Play: this is an abstract method and must be
    * implemented in any derived class.
    *
    * @param crazyEight gives access to the "draw pile".
    * @param prev       the previously played card.
    * @return a card from the player's hand.
    */
   public abstract Card play(Game crazyEight, Card prev);

   /**
    * Score: calculates the player's score (penalty points).
    * <p>
    * Note: as soon as a player has no cards, the game ends and
    * all other players score penalty points for their remaining cards.
    * Eights are worth 20, face cards are worth 10, and all others
    * are worth their rank.
    * </p>
    *
    * @return the score
    */
   public int score() {
      
      int points = 0;
      for (int i = 0; i < hand.size(); ++i) {
         if (hand.getCard(i).getRank() == 8) {
            points -= 20;
         }
         else if (hand.getCard(i).getRank() > 9) {
            points -= 10;
         }
         else {
            points -= hand.getCard(i).getRank();
         }
      } 
      return points;
   }

   /**
    * Display the cards in player's hand.
    */
   public void display() {
      System.out.println(name + "'s hand:");
      System.out.println(hand);
   }

   /**
    * Display the player's name and score.
    */
   public void displayScore() {
      System.out.println(name + " has " + score() + " points");
   }
}

