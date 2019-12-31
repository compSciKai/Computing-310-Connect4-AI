
#include <iostream>
using namespace std;

#include <vector>
#include <ctime>
//#include <algorithm>

// function definitions
void draw();
string play_a_new_game();
string get_player_input();

// globals
const int PLAYOUTS = 18500;
const int PO_DIFF = 1500; // play a few less for heuristic AI than montecarlo
const int DEPTH = 5;

const int GAME_TYPE = 2; // 0: Player vs Minimax-MonteCarlo Hybrid AI
                         // 1: Player vs Monte-Carlo AI
                         // 2: Minimax-MonteCarlo Hybrid AI vs Monte-Carlo AI

//---------------------------------------------------------------------
// Main Function
//---------------------------------------------------------------------

int main() {
string game_code = "y";
cout << "";
  while (game_code == "y") {
    game_code = play_a_new_game();

    // game codes: pw:player won, cw:computer won, d:draw, on r key press game code will be True
    if (game_code == "pw") { 
      bool incor_in = true; 
      while (incor_in) {
        cout << "\n\nYou win! would you like to play again? (press y/n) ";
        string x;
        cin >> x;
        if (x == "y") {
          game_code = "y";
          incor_in = false;
        }
        else if (x == "n") { 
          game_code = "no";
          incor_in = false;
        }
        else {
          cout << "please type y or n...";
        }
      }
    }
    else if (game_code == "cw") {
      bool incor_in = true;
      while (incor_in) {
        cout << "\n\nYou lose! would you like to play again? (press y/n) ";
        string x;
        cin >> x;
        if (x == "y") {
          game_code = "y";
          incor_in = false;
        }
        else if (x == "n") { 
          game_code = "no";
          incor_in = false;
        }
        else {
          cout << "please type y or n...";
        }
      }
    }
    else if (game_code == "d") {
      bool incor_in = true;
      while (incor_in) {
        cout << "Draw! would you like to play again? (press y/n)";
        string x;
        cin >> x;
        if (x == "y") {
          game_code = "y";
          incor_in = false;
        }
        else if (x == "n") { 
          game_code = "no";
          incor_in = false;
        }
        else {
          cout << "please type y or n...";
        }
      }
    }
    cout << "\n\nThanks for playing!\n";
  }
}

//---------------------------------------------------------------------
// Game Class
//---------------------------------------------------------------------

class Game {
  public:  // may want to change to private
    vector< vector<int> > board; // want to push 0s into this variable 
    vector<int> moves; // = {1, 2, 3, 4, 5, 6, 7};
    int turn; // = 1;  
    int full;
    //void parent = null;  // add in parent and children later
    //self.children = {}
    //int wins; // = 0;
    int num_moves; // = moves.size();
    //int num_children = len(self.children)
    //self.state = None  	// dont remember what this is for


    // constructor   

    Game() {
      //board.assign(7, vector<int> v.assign(6, 0);
      //for (int i; i < 42; i++) { board.push_back(0); }
      moves = {1, 2, 3, 4, 5, 6, 7};
      turn = 1;
      full = 0; // used to show computer turn when a column is full and child should not be used
      //wins = 0;
      num_moves = moves.size();
    }

    // copy constructor

    Game(const Game &obj) {
      //cout << "\ntesting: copy constructor called\n";
      //board = obj.board; // try vector copy constructor
      vector< vector<int> > temp(obj.board);
      //board(obj.board);
      board = temp; // try vector copy constructor
      vector<int> temp_moves(obj.moves);
      //moves = obj.moves;
      moves = temp_moves;
      turn = obj.turn;
      full = obj.full;
      num_moves = obj.num_moves;
      //cout << "\ntesting: copy constructor complete\n";
    }


    // class methods

    // initialization function

    void init() {
      int rows = 6;
      int cols = 7;
      // push all zeros to game board
      // or just push empty vectors of 6 **
      for (int i = 0; i < cols; i++) {
        vector<int> v; //(6); do we need size?
        v = {0, 0, 0, 0, 0, 0};
        board.push_back(v);
      }
    }

    

    // takes a turn in the game board

    bool take_turn(string move, string c) {
      int num = stoi(move);    // move is string: num is int
      int it = -1;
      for (int i = 0; i < 6; i++ ) {
        if ( board[num-1][i] == 0 ) { 
          it = i;
          break;
        }
      }

      // check if move is still in move list
      int it_moves = -1;
      for (int i = 0; i < num_moves; i++) {
        if ( num == moves[i] ) { it_moves = i; }
      }
      // if there is still a zero remaining: place token
      if ( it != -1) { board[ num-1 ][it] = turn; }
      // if there are no remaining slots, and column is still in moves list: remove it and return true
      else if ( it == -1 && it_moves != -1 ) {
        // remove the move and update num_moves
        vector<int>::iterator m_it = moves.begin();
        for (int i = 0; i < it_moves; i++)
          m_it++;
        moves.erase(m_it);
        num_moves = moves.size();
        if (turn != 2 && c != "c" ) cout << "can't move there";
        return true;
      }

      // if column is full and move has already been removed
      else { 
        cout << "can't move there";
        return true;
      }

      // change player's turn
      if ( turn == 1 ) { turn = 2; }
      else { turn = 1; }

      // return false: move successfull or true: stack is full
      return false;
    }

    void draw_game() {
      int rows = 6;
      cout << "\n";
      string cols[7];

      for ( int i = rows-1; i > -1; i-- ) {
        //cout << "starting i: " << i;
        for (int j = 0; j < 7; j++) {
          //cout << "board[j][0]: " << board[j][0];
          //if (board[j].size() <= i) { cols[j] = " "; }  // try to set if size > 6-i : i starts at 6 *** change with new heuristic
          if (board[j][i] == 0) { cols[j] = " "; }  // try to set if size > 6-i : i starts at 6 *** change with new heuristic
          else if ( board[j][i] == 1 ) { cols[j] = "X"; }
          else { cols[j] = "O"; }
        }
        cout << "\n  |" << cols[0] << "|" << cols[1] << "|" << cols[2] << "|" << cols[3] << "|" << cols[4] << "|" << cols[5] << "|" << cols[6] << "|";
        //cout << "finished i: " << i;  // << " j: " << j << "... ";
      }
      //cout << "\nending draw function after numbers...";
      cout << "\n   1 2 3 4 5 6 7 ";
      //cout << "testing";
    }

    // check win conditions

    string find_state() {
      int rows = 6;
      int cols = 7;
      string r_code = "n";

      // check rows   ** want to change around j+1 instead of i+1
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
          //if ( board[i][j] == 1  && board[i][j+1] && board[i][j+2] && board[i][j+3] == 1 ) { cout << "You win!"; }
          //else if ( board[i][j] == 1  && board[i][j+1] && board[i][j+2] && board[i][j+3] == 2 ) { cout << "Computer wins!"; }
          if ( board[j][i] == 1  && board[j+1][i] == 1 && board[j+2][i] == 1 && board[j+3][i] == 1 ) { 
            //cout << "\nYou win!\n"; 
            r_code = "pw";
          }
          else if ( board[j][i] == 2  && board[j+1][i] == 2 && board[j+2][i] == 2 && board[j+3][i] == 2 ) { 
            //cout << "\nComputer wins!\n"; 
            r_code = "cw";
          }
        }
      }
      //cout << "checked rows, r_code is: " << r_code;

      // check columns
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < 4; j++) {
          if ( board[i][j] == 1  && board[i][j+1] == 1 && board[i][j+2] == 1 && board[i][j+3] == 1 ) { 
            //cout << "\nYou win!\n"; 
            r_code = "pw";
          }
          else if ( board[i][j] == 2  && board[i][j+1] == 2 && board[i][j+2] == 2 && board[i][j+3] == 2 ) { 
            //cout << "\nComputer wins!\n"; 
            r_code = "cw";
          }
        }
      }
      //cout << "checked columns, r_code is: " << r_code;

      // check diagonals
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
          // player cases
          if ( (board[i][j+3] == 1)  && (board[i+1][j+2] == 1) && (board[i+2][j+1] == 1) && (board[i+3][j] == 1) ) { 
            //cout << "\nYou win!\n"; 
            r_code = "pw";
          }
          else if ( (board[i][j] == 1)  && (board[i+1][j+1] == 1) && (board[i+2][j+2] == 1) && (board[i+3][j+3] == 1) ) { 
            //cout << "\nYou win!\n"; 
            r_code = "pw";
          }
          // computer cases
          else if ( (board[i][j+3] == 2)  && (board[i+1][j+2] == 2) && (board[i+2][j+1] == 2) && (board[i+3][j] == 2) ) { 
            //cout << "\nComputer wins!\n"; 
            r_code = "cw"; 
          }
          else if ( (board[i][j] == 2)  && (board[i+1][j+1] == 2) && (board[i+2][j+2] == 2) && (board[i+3][j+3] == 2) ) { 
            //cout << "\nComputer wins!\n"; 
            r_code = "cw"; 
          }
        }
      }
      //cout << "checked diagonals, r_code is: " << r_code;

      // check if board is full
      int empty = 0;
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
          if (board[i][j] == 0) { empty = 1; break; }
        }
        if ( empty == 1 ) { break; }
      }
      if ( empty == 0 ) return "d";

      return r_code;
    }


    // functions to be implemented

    // add_child(self, game, move):
    // operator overloading
    //ostream& operator <<(
    
};

//---------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------

// draw an empty game board

void draw() {
  int rows = 6;
  //cout << "\n";
  for ( int i = 0; i < rows-1; i++ ) {
    cout << "  | | | | | | | |\n";
  }
  cout << "  | | | | | | | |";
  cout << "\n   1 2 3 4 5 6 7 ";
}

int minimax(Game g, int depth) { // g.turn chooses to min() or max() 2 for max, and 1 for min *** screws up if goes first?

  // figure out if player is first player or second player
  int mm;
  if (GAME_TYPE == 0) { mm = 2; }
  else if (GAME_TYPE == 2) { mm = 1; }
  // now algorithm knows to minimize or maximize

  // find state and calculate score
  int inf = 1000000;
  int score;
  if ( g.turn == mm ) { score = -(inf); } else { score = inf; } // set score to lowest possible for min or max
  if (g.full == 1) { return score; } // if column if full for this move, do nothing
  string state = g.find_state();
  // if caller is player 1
  if (GAME_TYPE == 2) {
    //if (state == "pw") { score = 1000+depth; }
    //else if (state == "cw") { score = -1000+depth; }
    if (state == "pw") { score = 1000; }
    else if (state == "cw") { score = -1000; }
    else  { score = 0; }
  }
  // if caller is player 2
  else if (GAME_TYPE == 0) {
    //if (state == "cw") { score = 1000+depth; }
    //else if (state == "pw") { score = -1000+depth; }
    if (state == "cw") { score = 1000; }
    else if (state == "pw") { score = -1000; }
    else  { score = 0; }
  }


  // if max depth reached
  if (depth == 0 || state != "n") return score;

  // otherwise run function

  // create child nodes
  int incor_mv = true;
  vector<Game> g_array;
  for ( int i = 0; i < g.num_moves; i++ ) {
    Game g_temp = g; 
    incor_mv = true;
    int move = g_temp.moves.at(i);
    incor_mv = g_temp.take_turn(to_string(move), "c");  // could this fail? not with loop? may want to conditionally remove moves
    if (incor_mv != false ) { g_temp.full = 1; }
    g_array.push_back(g_temp);  // should be 7 games
  }
  if (g_array.size() != 7) { cout << "Error: there should be 7 moves\n"; }


  int scores[g_array.size()];
  // minimax for each child
  //if (g.turn == 2) {
    for ( int i = 0; i < g_array.size(); i++) {
      if ( g_array.at(i).full == 1 ) { if (g.turn == mm) scores[i] = -(inf); else scores[i] = inf; continue; } 
      scores[i] = minimax(g_array[i], depth-1);
    }
  //}
  //int best_i;
  int best_m; 
  // if caller is player 1
  if ( GAME_TYPE == 2 ) {
    if ( g.turn == mm ) {
      best_m = -(inf); //Lowest Value
      for ( int i = 0; i < g_array.size(); i++) {
        if ( scores[i] > best_m ) { best_m = scores[i]; }
      }
    }
    else {
      best_m = inf; //Highest Value
      for ( int i = 0; i < g_array.size(); i++) {
        if ( scores[i] < best_m ) { best_m = scores[i]; }
      }
    }
  }
  // if caller is player 2
  if ( GAME_TYPE == 0 ) {
    if ( g.turn == mm ) {
      best_m = inf; //Highest Value
      for ( int i = 0; i < g_array.size(); i++) {
        if ( scores[i] < best_m ) { best_m = scores[i]; }
      }
    }
    else {
      best_m = -(inf); //Lowest Value
      for ( int i = 0; i < g_array.size(); i++) {
        if ( scores[i] < best_m ) { best_m = scores[i]; }
      }
    }
  }
  return best_m;
}

string computer_turn_mm(Game g) {
  int incor_mv = true;
  int r_move;
  int comp_it;
  int comp_move;
  int inf = 100000;

  // make sure game isn't full
  if (g.num_moves == 0) {
    return "d";
  }

  // create child nodes for both minimax and random playouts
  vector<Game> g_array;
  vector<Game> g_array_rp;
  for ( int i = 0; i < g.num_moves; i++ ) {
    Game g_temp = g; 
    incor_mv = true;
    int move = g_temp.moves.at(i);
    incor_mv = g_temp.take_turn(to_string(move), "c");  
    if (incor_mv != false ) { g_temp.full = 1; }
    g_array.push_back(g_temp); 
    g_array_rp.push_back(g_temp); 
  }

  // store scores for each move
  int scores[g_array.size()];

  // minimax for each child
  cout << "\n  Minimax Scores: ";
  for ( int i = 0; i < g_array.size(); i++) {
    if ( g_array.at(i).full == 1 ) { scores[i] = -(inf); continue; } // if column full, skip iteration
    //cout << "\nrunning minimax for child " << i << "...\n";
    scores[i] = minimax(g_array[i], DEPTH);
    cout << "T" << i+1 << ": " << scores[i] << " ";
  }
  cout << "\n";

  // find best moves and put them into an array
  int best_i = 0;
  int best_m = -(inf)-2; // will it ever return a score of same inf? yes, added -1
  vector<int> bests;
  for ( int i = 0; i < g_array_rp.size(); i++) { // changing this to g_rp
    if (best_m == scores[i]) { bests.push_back(i); } // cout << "\npushing turn " << i+1 << " to best moves"; }
    else if (best_m < scores[i] && best_m == -(inf)) { best_i = i; best_m = scores[i]; bests.push_back(i); } // cout << "\nnew best move " << i+1; }
    else if (best_m < scores[i] && best_m != -(inf)) { best_i = i; best_m = scores[i]; bests.clear(); bests.push_back(i); } //cout << "\nnew best move " << i+1; }
  } // not using best_i

  // play random playouts for each best move
  if (bests.size() != 1) {
    // set game board to full if not in best moves
    for ( int i = 0; i < g_array_rp.size(); i++) {
      bool in_array = false;
      for ( int j = 0; j < bests.size(); j++) {
        //cout << "\ni=" << i << " bests[j]=" << bests[j];
        if ( i == bests[j] ) { in_array = true; break; }
      }
      if ( in_array == false ) { g_array_rp[i].full = 1; } //cout << "\nmove " << i+1 << " is not a best move"; }
    }

    cout << "";

  // run monte carlo on best moves

  // push stats for each playout
  vector< vector<int> > stats; 

  // loop through each possible turn
  for ( int i = 0; i < g_array_rp.size(); i++) {
    vector<int> stat = {0, 0, 0};
    if ( g_array_rp.at(i).full == 1 ) { stats.push_back(stat); continue; } // if column full, skip iteration
    // loop through playouts 
        srand (time(NULL));
    for ( int j = 0; j < PLAYOUTS-PO_DIFF; j++) {
    //for ( int j = 0; j < PLAYOUTS; j++) {
      Game g_t = g_array_rp.at(i);
      string state = g_t.find_state();
      
      // look for current states to see if the first move forces a win state
      
      if (GAME_TYPE == 0) { // if caller is player 2
        if (state == "cw") { stat.at(0)+=1; continue; }
        else if (state == "pw") { stat.at(1)+=1; continue; }
        else if (state == "d") { stat.at(2)+=1; continue; } // may want to change to 0.5
      }
      else if (GAME_TYPE == 2) { // if caller is player 1
        if (state == "pw") { stat.at(0)+=1; continue; }
        else if (state == "cw") { stat.at(1)+=1; continue; }
        else if (state == "d") { stat.at(2)+=1; continue; } // may want to change to 0.5
      }

      //else { // else simulate more games     *** dont need this if other condition continues?
        while (state == "n") { // while no state

          // choose a random move
          incor_mv = true;
          int seed = 0;
          while(incor_mv) {
            seed += 1;
            comp_it = rand() %(g_t.num_moves);
            comp_move = g_t.moves.at(comp_it);
            incor_mv = g_t.take_turn(to_string(comp_move), "c");
          }

          // check state
          state = g_t.find_state();
          if (GAME_TYPE == 0) {
            if (state == "cw") { stat.at(0)+=1; } //cout << "computer win!"; }
            else if (state == "pw") { stat.at(1)+=1; }
            else if (state == "d") { stat.at(2)+=1; } // may want to change to 0.5
          }
          else if (GAME_TYPE == 2) {
            if (state == "pw") { stat.at(0)+=1; } //cout << "computer win!"; }
            else if (state == "cw") { stat.at(1)+=1; }
            else if (state == "d") { stat.at(2)+=1; } // may want to change to 0.5
          }
        }
      //} // else loop
    } // end of j loop

    stats.push_back(stat); // add stat to array
  } // end of i loop

  // find largest score
  int max_i = -1;
  int max = -10000;
  int wins;
  int draws;
  int losses;
  cout << "\n  Monte-Carlo Scores:\n";
  for ( int i = 0; i < stats.size(); i++ ) {
      wins = stats[i][0];
      losses = stats[i][1];
      draws = stats[i][2];
      cout << "  turn " << i+1 << ": { " << wins << " W /" << losses << " L /" << draws << " D }";
      int score = wins + draws/2;
      if (score > max) {
        //cout << "score greater than max...";
        max = score;
        max_i = i;
      }
      else if (score == max) {
        //cout << "score equal to max...";
        srand (time(NULL) + i*7);
        int ri = rand() %(2);
        cout << ri;
        if (ri == 1) { 
          max = score;
          max_i = i;
        }
      }
    cout << " score: " << score << "\n";
  }
    r_move = g.moves[max_i];
    cout << "\n  Simulations completed, ";
    //return to_string(move);

  //return to_string(r_move);
//}
  } // closing for if bests != 1
  else { r_move = g.moves[best_i]; cout << "  There was only one best move, so " << r_move << " was chosen\n"; }

  return to_string(r_move);
}


// computer_turn (monte-carlo)

string computer_turn(Game g) {
  int incor_mv = true;
  int r_move;
  int comp_it;
  int comp_move;
  if (g.num_moves == 0) {
    return "d";
  }

  // create child nodes
  vector<Game> g_array;
  int n = g.num_moves;
  for ( int i = 0; i < n; i++ ) {
    Game g_temp = g; 
    incor_mv = true;
    int move = g_temp.moves.at(i);
    //while(incor_mv) { 
    incor_mv = g_temp.take_turn(to_string(move), "c");  // could this fail? not with loop? may want to conditionally remove moves
    //}
    // if turn occurs on a full column
    if (incor_mv != false ) { g_temp.full = 1; }
    g_array.push_back(g_temp); 
  }
  //cout << g_array.size();
  incor_mv = true;

  // push stats for each playout
  vector< vector<int> > stats; 

  // loop through each possible turn
  for ( int i = 0; i < g_array.size(); i++) {
    vector<int> stat = {0, 0, 0};
    if ( g_array.at(i).full == 1 ) { stats.push_back(stat); continue; } // if column full, skip iteration
    // loop through playouts 
        srand (time(NULL));
    for ( int j = 0; j < PLAYOUTS; j++) {
      Game g_t = g_array.at(i);
      string state = g_t.find_state();
      
      // look for current states to see if the first move forces a win state
      if (state == "cw") { stat.at(0)+=1; continue; }
      else if (state == "pw") { stat.at(1)+=1; continue; }
      else if (state == "d") { stat.at(2)+=1; continue; } // may want to change to 0.5

      else { // else simulate more games
        while (state == "n") { // while no state

          // choose a random move
          incor_mv = true;
          int seed = 0;
          while(incor_mv) {
            seed += 1;
            //srand (time(NULL) + j +seed*7);
            comp_it = rand() %(g_t.num_moves);
            comp_move = g_t.moves.at(comp_it);
            //cout << "\nrandom move: " << comp_move;
            incor_mv = g_t.take_turn(to_string(comp_move), "c");
          }

          // check state
          state = g_t.find_state();
          if (state == "cw") { stat.at(0)+=1; } //cout << "computer win!"; }
          else if (state == "pw") { stat.at(1)+=1; }
          else if (state == "d") { stat.at(2)+=1; } // may want to change to 0.5
        }
      }
    }

    stats.push_back(stat); // add stat to array
  } // end of i loop
  // find largest score
  int max_i = -1;
  int max = -10000;
  int wins;
  int draws;
  int losses;
  for ( int i = 0; i < stats.size(); i++ ) {
      wins = stats[i][0];
      losses = stats[i][1];
      draws = stats[i][2];
      cout << "  turn " << i+1 << ": { " << wins << " W /" << losses << " L /" << draws << " D }";
      int score = wins + draws/2;
      if (score > max) {
        //cout << "score greater than max...";
        max = score;
        max_i = i;
      }
      else if (score == max) {
        cout << "score equal to max...";
        srand (time(NULL) + i*7);
        int ri = rand() %(2);
        cout << ri;
        if (ri == 1) { 
          max = score;
          max_i = i;
        }
      }
    cout << " score: " << score << "\n";
    }
    r_move = g.moves[max_i];
    cout << "\n  Simulations completed, ";
    //return to_string(move);

  return to_string(r_move);
}

// start a new game

string play_a_new_game() {
  clock_t time_spent;
  cout << "\nWelcome to Connect 4!\n";
  draw();
  cout << "";
  if (GAME_TYPE == 0 || GAME_TYPE == 1) {
  cout << "\n\nYou get to go first. Please select a move from the game above, or press \'r\' to reset the game.\n";
  }
  else { cout << "\n\nThe game has started with Hybrid MonteCarlo-Minimax (MCM) going first. \nHeuristicaly, it always chooses the center column if it is player one.\n"; }

  // turn = true means that it is the players turn
  bool turn = true;
  // game = true means that the game will continue to play out
  bool game = true;

  // instantiate the game
  Game g;
  g.init();
  bool first_turn = true;
  //int print = g.board;
  //cout << "\nGame class data:\n";
  //cout << "board.size = " << g.board.size();
  //cout << "\nnum_moves = " << g.num_moves;

  // start game loop
  while (game) {
    if ( turn == false ) {
      // computer takes turn
      string c_move;
      if (GAME_TYPE == 0) { 
        cout << "\n\n---------------------------------------------------------------------------\n";
        cout << "Hybrid MCM's turn...\n"; 
        cout << "\n  Statistics:\n"; 
      }
      else if (GAME_TYPE == 1 || GAME_TYPE == 2) { 
        cout << "\n\n---------------------------------------------------------------------------\n";
        cout << "Monte-Carlo's turn...\n"; 
        cout << "\n  Statistics:\n"; 
      }
      
      //string c_move = computer_turn(g);
      time_spent = clock();
      if (GAME_TYPE == 1 || GAME_TYPE == 2) { c_move = computer_turn(g); }
      else { c_move = computer_turn_mm(g); }
      time_spent = clock() - time_spent;
      cout << "turn took " << (float)time_spent/CLOCKS_PER_SEC << "s";
      if ( c_move == "d") { return "d"; }
      g.take_turn(c_move, "c");
      turn = true;
    }
    else {
      bool incor_mv = true;
      string c_in;
      while (incor_mv) {
        // player take turn
        if (GAME_TYPE == 0 || GAME_TYPE == 1) {
          string p_in = get_player_input();
          if (p_in == "r") {
            // returning true resets the game
            return "y";
          }
          incor_mv = g.take_turn(p_in, "p");
        }

        // Hybrid MCM Turn
        else { 
          cout << "\n\n---------------------------------------------------------------------------\n";
          cout << "Hybrid MCM's turn...\n"; 
         
          if (first_turn) {
            c_in = "4";
            first_turn = false;
          }
          else { 
            time_spent = clock();
            c_in = computer_turn_mm(g); 
            time_spent = clock() - time_spent;
            cout << "turn took " << (float)time_spent/CLOCKS_PER_SEC << "s";
          }
          incor_mv = g.take_turn(c_in, "c");
        }
      }
      turn = false; // turn this on when computer is implemented
    }
    // draw game with new move
    g.draw_game(); 
    // get game codes here
    string gc;
    gc = g.find_state();
    //cout << "\ngame code: " << gc;
    if (gc == "pw") { return "pw"; }
    else if (gc == "cw") { return "cw"; }
    else if (gc == "d") { return "d"; }
  }

  return "1"; // change this for real game
}

string get_player_input() { // has to return a string
  cout << "\n\nYour turn! Where would you like to move? ";
  bool output = false;
  string x;
  int integer;
  while (output == false) {
    //cout << "Please enter a number: "; 
    cin >> x;
    //cout << x;
    if ( x == "1" || x == "2" || x == "3" || x == "4" || x == "5" || x == "6" || x == "7" || x == "r" ) {
      //cout << "Correct input!\n";
      output = true;
    }
    else { 
      cout << "\nIncorrect input, type 'r' or a number from 1 to 7: "; 
      cin.clear();
      cin.ignore(256, '\n');
    }
  }
  //x = to_string(integer);
  return x;
}
 
//---------------------------------------------------------------------
// Code Graveyard
//---------------------------------------------------------------------

/* TODO ----------------------------------------------------------------
(*)     -  for each child -> simulate x playouts
(*)     -  in each playout
(*)        -  check inicial state
(*)        -  add score for a found state
(*)        -  loop through random moves until a state is found
(*)        -  check the scores for each turn 
( )  may want to add parent var in?
( )  
-- CRITERIA ------------------------------------------------------------
(*)  estimate how many playouts per second
(*)  make computer only take x seconds per turn
(*)  make huristic
(*)  write report
-- BUGS ----------------------------------------------------------------
(*)  player changes while computer takes turn
(*)  doesnt find any wins?
(*)  logged 30000 losses, are they only going through one column move?
----------------------------------------------------------------------*/

/* TODO ----------------------------------------------------------------
(*)  take player input and draw token on map
     -  implementing draw function
     -  need to figure out why zeros are showing after drawing
        -  set condition to put in zeros if size is not zero?
(*)  implement take turn function
(*)  change take turn function, draw, and init to draw zeros for 
     simplicity
     -  change back when adding in heuristic
(*)  check win conditions
(*)  implement player codes
     -  take out draw code
(*)  update play game function with computer's move
(*)  make computer take random move
(*)  need to re-implement draw
(*)  may want give the computer a set of moves, instead of randomly
     choosing columns that are full
(*)  update moves in game class (remove if column is full)
(*)  create computer_turn function
(*)  update play game function to call computer_turn
(*)  implement montecarlo
( )  -  create add child function
        - may not need this -> do all in computer_turn func
(*)  -  make a copy costructor
(?)     -  pass by reference
(*)  -  in computer turn funcion
(*)     -  create children from each possible move
-- BUGS ----------------------------------------------------------------
(*)  breaks when bottom row is full?
     -  breaks when anything put in 7th colum
     -  breaks in draw command? no
        -  doesn't draw board nubmers, or game code output
     -  breaks in find_state() command
     -  diagonal check called loop out of range
(*)  computer still chooses moves on full columns
     -  chooses the wrong moves to delete from moves list
     -  need to implement 'pick move from moves list'
(*)  iterator just deletes the first move in the array
     -  need to remove the move with a full column
(*)  breaks with 'double free or corruption (out)' at a win
     -  only for longer games, possibley with full columns?
     -  doesn't happen anymore... keep an eye on it
(*)  says 'you win' twice
(*)  computer player says 'cant move there' when thinking
(*)  copy constructor called after I created it, might cause a bug
(*)  computer_turn breaks after implementing montecarlo -> constructor
(*)  looks like function cannot access stats[i] in computer_turn function
----------------------------------------------------------------------*/

/*    while( !( cin >> integer ) ) { 
      if (x == "r") {
        cout << "reseting game...";
        return "r";
      }
      cout << "Please enter a number: "; 
    }
    cout << " ";
    if ((integer > 1) && (integer <= 7)) {
      cout << "Please select a number from 1 to 7:";
      // do nothing and restart the loop
    }
    else {
      cout << "Correct input!";
      output = true;
    }
*/
/*    // draw function
      for ( int i = rows-1; i > -1; i-- ) {
      //for ( int i = 0; i < rows; i++ ) {
        cout << "inside loop";
        string cols[7];
        for (int j = 0; j < 7; j++) {
          if ( board[j][i] == 0) { cols[j] = " "; }
          else if ( board[j][i] == 1 ) { cols[j] = "X"; }
          else { cols[j] = "O"; }
        }
        //cout << "| | | | | | | |\n";
*/
/*
    Game g_temp;
    cout << "\n    g_temp created";
    g_temp.board = g.board;
    cout << "\n    g.board copied";
    g_temp.moves = g.moves;
    cout << "\n    g.moves copied";
    g_temp.turn = g.turn;
    cout << "\n    g.turn copied";
    g_temp.num_moves = g.moves.size();
    cout << "\n    g.num_moves copied";
*/

// computer turn couts
    //while(incor_mv) { 
    //}
    // if turn occurs on a full column

  //Game g_array[g.num_moves];
  //cout << "\n  g_array created";
  //cout << "\n  g.num_moves =" << g.num_moves;
    //cout << "\n  loop for children at i=" << i;
    //cout << "starting while loop";
    //while (incor_mv) { 
      //cout << "adding child for i=" << i;
    //}
    //g_array[i] = g_temp;
  //cout << "outside of loop";
  // for each child: simulate x random playouts
      //Game *g_t = new Game();
      //*g_t = g_array[i];
      //string state = g_t->find_state();
            //comp_it = rand() %(g.num_moves) +1;
            //comp_it = rand() %(g_t->num_moves);
            //cout << "computer chooses move num " << comp_it << " in the moves array...\n";
            //comp_move = g_t->moves[comp_it];
            //cout << "num " << comp_it << " in moves array is " << comp_move << "...\n";
            //incor_mv = g_t->take_turn(to_string(comp_move));
          //state = g_t->find_state();
      //delete g_t;

// take turn scrap

      //cout << "\ntake_turn function: \n";
      //cout << "  num = " << num << "\n";
          //it = board[num-1][i];
 
      // check that stack for that move is not full & push player int to stack
          // board[ column ][ row ];
      //cout << "column " << num << " inicially had a size of: " << board[num].size() << "\n";
      //if ( board[ num-1 ].size() < 6) { board[ num-1 ].push_back(turn); }			// ** for hueristic

      // find location of lowest zero in column
/*
      cout << "  zero column iterator = " << it << "\n";

      cout << "checking moves list...\n";
      cout << "  num: " << num << "\n";
*/
        //cout << "  moeves[i]: " << moves[i] << "\n";
      //cout << "  move array iterator = " << it_moves << "\n";

      //if ( it == -1) { cout << "lowest zero not found..."; }
      //if ( board[ num-1 ].size() < 6) { board[ num-1 ].push_back(turn); }  // change to change zeros to turn
        //m_it--;
        //m_it+it_moves-1;
        //m_it+it_moves-1;
/*
        for (auto i = moves.begin(); i != moves.end(); i++) {
          if (moves.at(i) == num) { m_in = i; }
        }
*/
        //cout << "removing move: " << *m_it;
        //cout << "\nmoves list now:";
        //for (int i = 0; i < num_moves; i++) { cout << moves[i] << ", "; }
/*
      // output
      cout << "column " << num << " now has values: ";
      for (int i = 0; i < board[num-1].size(); i++ )
        cout << board[num-1][i] << ", "; // have to overload?
      cout << "\n";
*/
/*
      int it = -1;
      for (int i; i < num_moves; i++) {
        if ( moves[i] == num ) it = i; 
      }
*/

// random move in computer_turn function

  // choose a random move
/*
  incor_mv = true;
  while(incor_mv) {
    srand (time(NULL));
    //comp_it = rand() %(g.num_moves) +1;
    comp_it = rand() %(g.num_moves);
    //cout << "computer chooses move num " << comp_it << " in the moves array...\n";
    comp_move = g.moves.at(comp_it);
    //cout << "num " << comp_it << " in moves array is " << comp_move << "...\n";
    incor_mv = g.take_turn(to_string(comp_move));
  }
  return to_string(comp_move);
*/

// minimax scrap


/*
  if (g.turn == 2) { return std::max( minimax(g_array[0], depth-1), minimax(g_array[1], depth-1), minimax(g_array[2], depth-1),   
              minimax(g_array[3], depth-1), minimax(g_array[4], depth-1), minimax(g_array[5], depth-1), 
              minimax(g_array[6], depth-1)); }    

  else { return std::min( minimax(g_array[0], depth-1), minimax(g_array[1], depth-1), minimax(g_array[2], depth-1),   
              minimax(g_array[3], depth-1), minimax(g_array[4], depth-1), minimax(g_array[5], depth-1), 
              minimax(g_array[6], depth-1)); }    
*/
