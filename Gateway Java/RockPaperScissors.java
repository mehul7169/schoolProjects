import java.util.Scanner;
import java.util.Random;
/**
* The Rock-paper-scissors Game!
*/
public class RockPaperScissorsGameV2 {
   /**
   *getting the user choice.
   *@return character commond
   */

   public static char getUserChoice() {
      char userChoice;
      int randomUserNumber = 0;
      Scanner scnr = new Scanner(System.in);
      System.out.print("[R]ock, [P]aper, or [S]cissors? ");
      String userInput = scnr.next();
      userChoice = userInput.charAt(0);
      return userChoice;
   }
   /**
   *getting the computer choice.
   *@return character commmand
   *@param character
   */
   public static char getSystemChoice() {
      String computerChoice = "";
      Random r = new Random();
      int randomNumber = r.nextInt(3);
         
      if (randomNumber == 0) {
         computerChoice = "R";
      }
      else if (randomNumber == 1) {
         computerChoice = "P";
      }
      else if (randomNumber == 2) {
         computerChoice = "S";
      }
      char computerPick = computerChoice.charAt(0);
      return computerPick;
   }  
   /**
   *displaying the computer choice and user choice.
   * @param userChoice dsiplays user Choice
   * @param computerChoice displays computerChoice
   */  
   public static void displayChoices(char userChoice, char computerChoice) {
      String computerFullChoice = "";
      String userFullChoice = "";
      String userPick = Character.toString(userChoice);
      userPick = userPick.toUpperCase();
      String computerPick = Character.toString(computerChoice);
      if (userPick.equals("P")) {
         System.out.println("User: Paper!");
      }
      else if (userPick.equals("S")) {
         System.out.println("User: Scissors!");
      }
      else if (userPick.equals("R")) {
         System.out.println("User: Rock!");
      }
      else {
         
         System.out.println("You  made an invalid choice!");
         System.out.println("Terminating the program."); 
         System.exit(0);
      }
      if (computerPick.equals("P")) {
         System.out.println("System: Paper!");
      }
      else if (computerPick.equals("S")) {
         System.out.println("System: Scissors!");
      }
      else if (computerPick.equals("R")) {
         System.out.println("System: Rock!");
      }
   }
   /**
   *finding the winner.
   * @param userChoice character for the choice of user
   * @param computerChoice character for the choice of computer
   */
   public static void displayTheWinner(char userChoice, char computerChoice) {
      displayChoices(userChoice, computerChoice);
      String userPick = Character.toString(userChoice);
      userPick = userPick.toUpperCase();
      String computerPick = Character.toString(computerChoice);
      
      if ((computerPick.equals("P") && userPick.equals("P")) || 
         (computerPick.equals("R") && userPick.equals("R")) || 
         (computerPick.equals("S") && userPick.equals("S"))) {
         System.out.println(">>> It's a draw <<<");
      }
      else if ((computerPick.equals("R") && userPick.equals("S")) 
         || (computerPick.equals("S") && userPick.equals("P")) 
         || (computerPick.equals("P") && userPick.equals("R"))) {
         System.out.println(">>> System wins! <<<");
      
      }
      else {
         System.out.println(">>> User wins! <<<");
      }
   
   }
    /**
    * Execution starts here.
    * @param args command-line arguments.
    */
   public static void main(String[] args) {
      char userChoice = getUserChoice();
      char systemChoice = getSystemChoice();
      displayTheWinner(userChoice, systemChoice);  
   }
}
