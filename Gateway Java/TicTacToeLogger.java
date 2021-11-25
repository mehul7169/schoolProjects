import java.util.Scanner;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.IOException;


/**
 *  Two-player game of Tic-Tac-Toe.
 *
 *  This is a paper-and-pencil game for two players,
 *  <code>X</code> and <code>O</code>, who take turns
 *  marking the spaces in a <code>n</code> x <code>n</code>
 *  grid (usually 3 x 3).
 *  The player who succeeds in placing <code>n</code> of their
 *  marks in a horizontal, vertical, or diagonal row wins the game.
 */
public class TicTacToeLogger {
   /** A final variable to indicate state of the game. */
   private static final int WIN = 1;
   /** A final variable to indicate state of the game. */
   private static final int IN_PROGRESS = 0;
   /** A final variable to indicate state of the game. */
   private static final int TIE = -1;
   /** Player-1 marker. */
   private static final char CROSS = 'X';
   /** Player-2 marker. */
   private static final char NOUGHT = 'O';
   /** A final variable to indicate player-1. */
   private static final int PLAYER_ONE = 0;
   /** A final variable to indicate player-2. */
   private static final int PLAYER_TWO = 1;
   /** Size of board can be 3 or 4. */
   private static final int SIZE = 3;


   /**
    * Execution starts here.
    * @param args  command-line arguments.
    @throws IOException its because there is a chance that file crashes
    */
   public static void main(String[] args) throws IOException {
      // Do not make any changes to main!
      Scanner keyboard = new Scanner(System.in);
      FileOutputStream fileOutStream = new FileOutputStream("log.txt");
      PrintWriter outFS = new PrintWriter(fileOutStream);
      char[] markerForPlayer = {CROSS, NOUGHT};
      char[] board = new char[SIZE * SIZE];
      int status = IN_PROGRESS;
      int player = PLAYER_TWO;
   
      initBoard(board);
   
      while (status == IN_PROGRESS) {
         player = switchPlayer(player);
         displayBoard(markerForPlayer, board, outFS);
         makeMove(keyboard, board, player, markerForPlayer[player]);
         status = updateStatus(board, markerForPlayer[player]);
      }
   
      displayBoard(markerForPlayer, board, outFS);
      displayResult(status, player);
      outFS.flush();
      fileOutStream.close(); // close() may throw IOException if fails
   }

   /**
    * Converts <code>row</code> and <code>col</code> indices into
    * linear index of a corresponding row-major 1D array.
    * @param row index of row.
    * @param col index of column.
    * @return non-negative integer.
    */
   public static int getLinearIndex(int row, int col) {
      return row * SIZE + col;
   }

   /**
    * Initializes the tic-tac-toe board with numbers
    * that can be used by players to indicate which
    * position they want to mark.
    * @param board  the tic-tac-toe board
    */
   public static void initBoard(char[] board) {
      char next = '0';
      int index;
      for (int row = 0; row < SIZE; row++) {
         for (int col = 0; col < SIZE; col++) {
            index = getLinearIndex(row, col);
            board[index] = next;
            next++;
            if (next == '9' + 1) {
               next = 'a'; // put hex values in cells
            }
         }
      }
   }

   /**
    * Switch from one player to the other.
    * @param player  the current player.
    * @return the next player.
    */
   public static int switchPlayer(int player) {
      if (player == 0) { 
         return 1;
      }
      else {
         return 0;
      }
   }

   /**
    * Performs a single move for given <code>player</code>;
    * rejects moves to cells that are already occupied
    * and prompts user to choose again.
    * Assume: user enters a valid number corresponding
    * to a position on the board.
    * @param board  the tic-tac-toe board.
    * @param keyboard for scanner
    * @param player  the player whose turn is next.
    * @param marker  the character the player uses to
    * mark a position on the board
    */
   public static void makeMove(Scanner keyboard, 
      char[] board, int player, char marker) {
      int choice;
   
      do {
         System.out.printf("\nPlayer %d, enter a number: ", player);
         choice = keyboard.nextInt();
      } while (!updateBoard(board, choice, marker));
   
   }

   /**
    * Marks selected cell on <code>board</code> with given <code>marker</code>.
    * if <code>choice</code> is valid and cell is not already occupied.
    * @param board  the tic-tac-toe board.
    * @param choice  the cell to be marked.
    * @param marker  the character used to mark the cell.
    * @return <code>true</code> if cell is empty and successfully marked,
    * <code>false</code> if choice is not valid or cell
    * has already been marked.
    */
   public static boolean updateBoard(char[] board,
       int choice, char marker) {
      if (board[choice] == 'X' || board[choice] == 'O') {
         return false;
      }
      else {
         board[choice] = marker; 
         
      
         return true;
      }
   }

   /**
    * Update game status : check for win or tie
    * for player with given <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to check.
    * @return <code>WIN</code> if player with marker has won;
    * <code>IN_PROGRESS</code> if game has not yet ended;
    * <code>TIE</code> if game is tied.
    */
   public static int updateStatus(char[] board, char marker) {
      
      if (checkRows(board, marker) 
         || checkCols(board, marker) || checkDiagonals(board, marker)) {
         return WIN;
      }
      else if (!checkRows(board, marker)
               && !checkCols(board, marker)
               && !isBoardFull(board)
               && !checkMainDiagonal(board, marker)
               && !checkCounterDiagonal(board, marker)) {
         return IN_PROGRESS;
      } 
      return TIE;
   }

   /**
    * Checks if there is a row filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if there is a row filled with marker,
    * <code>false</code> otherwise
    */
   public static boolean checkRows(char[] board, char marker) {
      for (int row = 0; row < SIZE; row++) {
         if (checkRow(board, row, marker)) {
            return true;
         }
      }
   
      return false;
   }

   /**
    * Checks if row is filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param row  index of row to be checked.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if row is filled with marker,
    * <code>false</code> otherwise.
    */
   public static boolean checkRow(char[] board, int row, char marker) {
      return (board[row * 3] == marker 
         && board[row * 3 + 1] == marker && board[row * 3 + 2] == marker);
   }

   /**
    * Checks if there is a column filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if there is a column filled with
    * <code>marker</code>, <code>false</code> otherwise.
    */
   public static boolean checkCols(char[] board, char marker) {
      for (int col = 0; col < SIZE; col++) {
         if (checkCol(board, col, marker)) {
            return true;
         }
      }
   
      return false;
   }

   /**
    * Checks if column is filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param col  index of column to be checked.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if specified column is filled
    * with marker <code>false</code> otherwise.
    */
   public static boolean checkCol(char[] board, int col, char marker) {
      
   
      return (board[col] == marker 
         && board[col + 3] == marker 
         && board[col + 6] == marker);
   }

   /**
    * Checks if there is a diagonal filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if there is a diagonal filled
    * with <code>marker</code>, <code>false</code> otherwise.
    */
   public static boolean checkDiagonals(char[] board, char marker) {
      return (checkMainDiagonal(board, marker)
         || checkCounterDiagonal(board, marker));
   }

   /**
    * Checks if main diagonal is filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if main diagonal is filled with
    * <code>marker</code>, <code>false</code> otherwise.
    */
   public static boolean checkMainDiagonal(char[] board, char marker) {
      return (board[0] == CROSS 
         && board[4] == CROSS && board[8] == CROSS);
   }

   /**
    * Checks if counter diagonal is filled with <code>marker</code>.
    * @param board  the tic-tac-toe board.
    * @param marker  the marker to be checked.
    * @return <code>true</code> if counter diagonal is filled with
    * <code>marker</code>, <code>false</code> otherwise.
    */
   public static boolean checkCounterDiagonal(char[] board, char marker) {
      return (board[6] == marker 
         && board[4] == marker && board[2] == marker);
      
      
   }

   /**
    * Checks to see if <code>board</code> is full.
    * @param board  the tic-tac-toe board.
    * @return <code>true</code> if <code>board</code> is full,
    * <code>false</code> otherwise.
    */
   public static boolean isBoardFull(char[] board) {
      int count = 0;
      for (int i = 0; i < SIZE * SIZE; ++i) {
         if (board[i] == CROSS || board[i] == NOUGHT) {
            ++count;
         }
      }
      return (count == SIZE * SIZE);
   }

   /**
    * Displays final result.
    * @param status  the game status.
    * @param player  the player who won (if game was not tied).
    */
   public static void displayResult(int status, int player) {
      System.out.print("\n\n*****");
      if (status == WIN) {
         System.out.printf(" Player %d won! ", player);
      }
      else {
         System.out.print(" It's a draw! ");
      }
      System.out.print("*****\n\n");
   }

   /**
    * Displays the board.
    * @param markerForPlayer  array of markers used by players.
    * @param board  the tic-tac-toe board.
    @param outFS to output
    */
   public static void displayBoard(char[] markerForPlayer, 
      char[] board, PrintWriter outFS) {
      displayHeader(markerForPlayer);
      for (int row = 0; row < SIZE; row++) {
         displayBoardRowSeparator(outFS);
         displayBoardRow(board, row, outFS);
      }
      displayBoardRowSeparator(outFS);
   }

   /**
    * Displays header showing markers used by each player.
    * @param markerForPlayer  array of markers used by players.
    */
   public static void displayHeader(char[] markerForPlayer) {
      System.out.print("\n\nTic Tac Toe\n");
      System.out.printf("Player %d [%c], Player %d [%c]\n\n",
             PLAYER_ONE, markerForPlayer[PLAYER_ONE],
             PLAYER_TWO, markerForPlayer[PLAYER_TWO]);
   }

   /**
    * Displays single row of board.
    * @param board  the tic-tac-toe board.
    * @param row  index of row to be displayed.
    @param outFS to output
    */
   public static void displayBoardRow(char[] board,
      int row, PrintWriter outFS) {
      int index;
      for (int col = 0; col < SIZE; col++) {
         index = getLinearIndex(row, col);
         outFS.print("|");
         System.out.print("|");
         System.out.printf(" %c ", board[index]);
         outFS.printf(" %c ", board[index]);
      }
      System.out.print("|\n");
      outFS.print("|\n");
   }

   /** Display row separator for tic-tac-toe board.
   @param outFS to output to new file */
   public static void displayBoardRowSeparator(PrintWriter outFS) {
      int rowSize = SIZE * 4 + 1;
      for (int count = 0; count < rowSize; count++) {
         System.out.print("-");
         outFS.print("-");
      }
      System.out.println();
      outFS.println();
   }
}