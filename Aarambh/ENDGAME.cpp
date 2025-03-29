#include <iostream> //input ouput stream library h  cin,cout functions hm iski mddat se he use kr paate h
#include<algorithm> //algorithm library hm iski mddat se he inbuilt function use kr paate h
#include <map> //used for board mapping with numbers
#include <cstdlib> //used for random number generation
#include <ctime> //used for random number generation
#include <vector> //used for vector
using namespace std;
//FUNCTIONS FOR UNBEATABLE A.I. 
//1ST FUNCTION WHICH EVALUATE EACH POSSIBLE MOVE
int evaluate(char TIC[3][3], char playersign, char AIsign) {
    for (int row = 0; row < 3; row++) {
        if (TIC[row][0] == TIC[row][1] && TIC[row][1] == TIC[row][2]) {
            if (TIC[row][0] == AIsign) return +10;
            if (TIC[row][0] == playersign) return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (TIC[0][col] == TIC[1][col] && TIC[1][col] == TIC[2][col]) {
            if (TIC[0][col] == AIsign) return +10;
            if (TIC[0][col] == playersign) return -10;
        }
    }   //ye function agr AI jita toh +10 return kr dega agr player jita toh -10 return kr dega or draw hua toh 0 return kr dega
    if (TIC[0][0] == TIC[1][1] && TIC[1][1] == TIC[2][2]) {
        if (TIC[0][0] == AIsign) return +10;
        if (TIC[0][0] == playersign) return -10;
    }
        
    if (TIC[0][2] == TIC[1][1] && TIC[1][1] == TIC[2][0]) {
        if (TIC[0][2] == AIsign) return +10;
        if (TIC[0][2] == playersign) return -10;
    }
    return 0;
}

// Minimax algorithm to find the best move
int minimax(char TIC[3][3], int depth, bool isMax, char playersign, char AIsign) {
    int score = evaluate(TIC, playersign, AIsign);
//ismax hme indicate krta h ki ye AI ka move h ya player ka move
    if (score == 10) return score - depth;  //AI jit chuka hai, lekin jitni jaldi jeetega, utna acha hai isi liye depth ko minus kiya 
    if (score == -10) return score + depth; //Agar player jeet raha hai, toh AI jitna late hoga, utna acha hai isi liye depth ko plus kiya

    bool movesLeft = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (TIC[i][j] != 'X' && TIC[i][j] != 'O') {
                movesLeft = true;
                break;
            }
        }
    }
    if (!movesLeft) return 0; //condition for draw

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (TIC[i][j] != 'X' && TIC[i][j] != 'O') {
                    char backup = TIC[i][j];
                    TIC[i][j] = AIsign;            // AI's move
                    best = max(best, minimax(TIC, depth + 1, false, playersign, AIsign));      //recursion k thru apna maximize krega
                    TIC[i][j] = backup;            //backtracking
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (TIC[i][j] != 'X' && TIC[i][j] != 'O') {
                    char backup = TIC[i][j];
                    TIC[i][j] = playersign;
                    best = min(best, minimax(TIC, depth + 1, true, playersign, AIsign));  //recursion k thru apna minimize krega yani player k minimize
                    TIC[i][j] = backup;
                }
            }
        }
        return best;
    }
}

// Function to select the best move for the computer
int findBestMove(char TIC[3][3], char AIsign, char playersign) {
    int bestVal = -1000;
    int bestMove = -1;                       // Yeh algorithm har move ka future dekhke best move choose karti hai, taaki jetne ke chances maximum ho

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (TIC[i][j] != 'X' && TIC[i][j] != 'O') {
                char backup = TIC[i][j];
                TIC[i][j] = AIsign;
                int moveVal = minimax(TIC, 0, false, playersign, AIsign);
                TIC[i][j] = backup;

                if (moveVal > bestVal) {
                    bestMove = i * 3 + j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
//----------------------------------------------------------------------------------------------------------
// Function to print the board
void print(char TIC[3][3]) {
    cout << "Current Board:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {             //ye function pointer input m leta h 
            cout << TIC[i][j];                     //ye function hr move k baad board print krta h
            if (j < 2) cout << " | "; 
        }
        cout << endl;
        if (i < 2) cout << "---------\n"; 
    }
}
//----------------------------------------------------------------------------------------------------------
// Function to check for a winner or draw
bool iswin(char TIC[3][3], int playersign, int AIsign) {
    // Check rows, columns, and diagonals for a winner
    for (int i = 0; i < 3; i++) {
        if (TIC[i][0] == TIC[i][1] && TIC[i][1] == TIC[i][2]) {
            if (TIC[i][0] == playersign) return true;            //column win check krega 
            if (TIC[i][0] == AIsign) return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (TIC[0][i] == TIC[1][i] && TIC[1][i] == TIC[2][i]) {
            if (TIC[0][i] == playersign) return true;                    //row win check krega
            if (TIC[0][i] == AIsign) return true;
        }
    }
    if (TIC[0][0] == TIC[1][1] && TIC[1][1] == TIC[2][2]) {
        if (TIC[0][0] == playersign) return true;
        if (TIC[0][0] == AIsign) return true;                     
    }                                                                    //diagonal win check krega
    if (TIC[0][2] == TIC[1][1] && TIC[1][1] == TIC[2][0]) {
        if (TIC[0][2] == playersign) return true;
        if (TIC[0][2] == AIsign) return true;
    }

    // Check if it's a draw
    bool isDraw = true;
    for (int i = 1; i <= 9; i++) {
        if (TIC[(i-1)/3][(i-1)%3] != 'X' && TIC[(i-1)/3][(i-1)%3] != 'O') {
            isDraw = false;                                                              ////draw check krega
                                                                        //jb pura board full ho jayega to draw ho jayega
            break;
        }
    }
    return isDraw;
}
//////ye sb AI k liye tha ...............
//---------------------------------------------------------------------------------------------------------- 



// //player game k liye 
// bool iswin(char TIC[3][3], int &player1win, int &player2win, map<int, char> boardmap,int player1sign,int player2sign) {
//     // Check for winning conditions in rows
//     for (int i = 0; i < 3; i++) {
//         if (TIC[i][0] == TIC[i][1] && TIC[i][1] == TIC[i][2]) {
//             if (TIC[i][0] == player1sign) {
//                 player1win = 1;
//                 return true;
//             } else if (TIC[i][0] == player2sign) {
//                 player2win = 1;
//                 return true;
//             }
//         }
//     }
//     // Check for winning conditions in columns
//     for (int i = 0; i < 3; i++) {
//         if (TIC[0][i] == TIC[1][i] && TIC[1][i] == TIC[2][i]) {
//             if (TIC[0][i] == player1sign) {
//                 player1win = 1;
//                 return true;
//             } else if (TIC[0][i] == player2sign) {
//                 player2win = 1;
//                 return true;
//             }
//         }
//     }
//     // Check for winning conditions in diagonals
//     // Left to right diagonal
//     if (TIC[0][0] == TIC[1][1] && TIC[1][1] == TIC[2][2]) {
//         if (TIC[0][0] == 'X') {
//             player1win = 1;
//             return true;
//         } else {
//             player2win = 1;
//             return true;
//         }
//     }

//     // Right to left diagonal
//     else if (TIC[0][2] == TIC[1][1] && TIC[1][1] == TIC[2][0]) {
//         if (TIC[0][2] == player1sign) {
//             player1win = 1;
//             return true;
//         } else {
//             player2win = 1;
//             return true;
//         }
//     }

//     // Check for draw condition
//     for (int i = 1; i < 10; i++) {
//         if (boardmap[i] == 'X' || boardmap[i] == 'O') {
//             if (i == 9) { // If all spots are filled
//                 player1win = 1;
//                 player2win = 1;                                                     //
//                 return true;
//             }
//         } else {
//             return false; // Game is still ongoing
//         }
//     }

//     return false;
// }
//------------------------------------------------------------------------------------------------------------
// Function to generate a random move for the computer
int getRandomMove(char TIC[3][3]) {
    vector<int> available_moves;          //ye vector available moves ko store krta h
    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        if (TIC[row][col] != 'X' && TIC[row][col] != 'O') {
            available_moves.push_back(i);
        }
    }

    // Check if there are no available moves
    if (available_moves.empty()) {
        return -1; // Return -1 if no valid move exists
    }

 int random_index = rand() % available_moves.size();//RAND() GENERATE SOME RANDOM NO.

    //WHEN WE DIVIDE THE RANDOM NO. WITH THE SIZE OF THE VECTOR IT WILL GIVE THE INDEX OF THE RANDOM NO. IN THE VECTOR AS THR RANDOM INDEX availble moves k indexes ki range m he hoga
    return available_moves[random_index];
}



// Function to check if there is a winner or if the game is a draw for computer 
bool iswin(char TIC[3][3], int &playerwin, int &computerwin, map<int,char> &boardmap,int playersign,int computersign) {
    // Check for winning conditions in rows
    for (int i = 0; i < 3; i++) {
        if (TIC[i][0] == TIC[i][1] && TIC[i][1] == TIC[i][2]) {
            if (TIC[i][0] == playersign) {
                playerwin = 1;
                return true;
            } else if (TIC[i][0] == computersign) {
                computerwin = 1;
                return true;
            }
        }
    }
    // Check for winning conditions in columns
    for (int i = 0; i < 3; i++) {
        if (TIC[0][i] == TIC[1][i] && TIC[1][i] == TIC[2][i]) {
            if (TIC[0][i] == playersign) {
                playerwin = 1;
                return true;
            } else if (TIC[0][i] == computersign) {
                computerwin = 1;
                return true;
            }
        }
    }

    // Check for winning conditions in diagonals
    if (TIC[0][0] == TIC[1][1] && TIC[1][1] == TIC[2][2]) {
        if (TIC[0][0] == playersign) {
            playerwin = 1;
            return true;
        } else if (TIC[0][0] == computersign) {
            computerwin = 1;
            return true;
        }
    }
    if (TIC[0][2] == TIC[1][1] && TIC[1][1] == TIC[2][0]) {
        if (TIC[0][2] == playersign) {
            playerwin = 1;
            return true;
        } else if (TIC[0][2] == computersign) {
            computerwin = 1;
            return true;
        }
    }

    // Check for draw condition
    bool isDraw = true;
    for (int i = 1; i <= 9; i++) {
        if (boardmap[i] != 'X' && boardmap[i] != 'O') {
            isDraw = false; // There's still an empty spot
            break;
        }
    }
    if (isDraw) {
        playerwin = 1;
        computerwin = 1;
        return true;
    }

    return false;
}
//-----------------------------------------------------------------------------------------
int main() {
    int a;
    cout<<"Enter 1 to play with computer(🤖) or 2 to play with friend (🙍‍♂️ or 🙍‍♀️) and 3 for play with !unbeatable A.I.(👽👽) : ";
    cin>>a;
    if(a==1){
        cout<<endl<<"YOU ARE PLAYING WITH COMPUTER:----:"<<endl;
        srand(time(0)); // Seed the random number generator it generates random no time(0) current time dega seconds srand hmne isi liye use kiya h taki hm  hr baar unique no. generate kr ske agr hmne iski jgh rand() toh wo hr baar same sequence of no. generate krta

        // Tic-Tac-Toe game setup
        char TIC[3][3] = {{'1', '2', '3'},
                          {'4', '5', '6'},
                          {'7', '8', '9'}};
        cout << "🙏🙏 WELCOME 🙏🙏 TO TIC TAC TOE ⚔️ (❌ or ⭕) ⚔️! " << endl;

        // Player and computer symbols
        char playersign, computersign;
        cout << "PLAYER , CHOOSE 'X' OR 'O': ";
        cin >> playersign;

        // Validate player symbol selection
        while (true) {
            if (playersign == 'X' || playersign == 'x') {
                playersign = 'X';
                computersign = 'O';
                break;
            } else if (playersign == 'O' || playersign == 'o') {    //player aak sign choose krega
                playersign = 'O';
                computersign = 'X';
                break;
            } else {
                cout << "Invalid input.🤬🤬 Please choose 'X' or 'O': ";
                cin >> playersign;
            }
        }

        cout << "SYMBOL FOR PLAYER : " << playersign << endl;
        cout << "SYMBOL FOR COMPUTER: " << computersign << endl;                    //symbol  display kradiye

        print(TIC);
        cout << "WARNING: Enter numbers between 1 and 9 only!" << endl;           //warning message

        map<int, char> boardmap;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {                               //board ki mapping ki h  taki  hm  move chl ske number enter krke
                boardmap[i * 3 + j + 1] = TIC[i][j];
            }
        }

        int playerwin = 0, computerwin = 0;
        int playerwins = 0, computerwins = 0;
        int playermove, computermove, count = 1;

        while (count != -1) {  //THIS LOOP WILL RUN UNTIL THE GAME IS OVER          ye loop tb tk end nhi hogi jb tk game end nhi ho jayegi
            while (playerwin != 1 && computerwin != 1) {        // jb tk koi bhi nhi jita
                // Player move
                if (!iswin(TIC, playerwin, computerwin, boardmap,playersign,computersign)) {
                    cout << "PLAYER  MOVE: ";
                    cin >> playermove;
                    if (playermove >= 1 && playermove <= 9 && boardmap[playermove] != 'X' && boardmap[playermove] != 'O') {
                        boardmap[playermove] = playersign;
                        TIC[(playermove - 1) / 3][(playermove - 1) % 3] = playersign;
                        print(TIC);
                    }
                    else {
                        cout << "INVALID MOVE PLAYER  🤬🤬" << endl;
                    }
                }

                // Computer move
                if (!iswin(TIC, playerwin, computerwin, boardmap,playersign,computersign)) {
                    computermove = getRandomMove(TIC);
                     cout<<"COMPUTER MOVE IS :-->"<<computermove<<endl;
                    if (computermove >= 1 && computermove <= 9 && boardmap[computermove] != 'X' && boardmap[computermove] != 'O')
                    {
                        boardmap[computermove] = computersign;
                        TIC[(computermove - 1) / 3][(computermove - 1) % 3] = computersign;
                        print(TIC);
                    }
                }

                // Check for winner
                iswin(TIC, playerwin, computerwin, boardmap,playersign,computersign);
                if (playerwin == 1 && computerwin == 1) {
                    cout << "DRAW! 😳😳" << endl;
                } else if (playerwin == 1) {
                    cout << "PLAYER  WON THE GAME 🥳🥳" << endl;
                    playerwins++;
                } else if (computerwin == 1) {
                    cout << "COMPUTER WON THE GAME 🥳🥳" << endl;
                    computerwins++;
                }
            }

            // Play again?
            cout << "DO YOU WANT TO PLAY AGAIN? ENTER -1 TO EXIT OR 1 TO CONTINUE: ";
            cin >> count;
            if (count == 1) {
                // Reset game
                char newTIC[3][3] = {{'1', '2', '3'},
                                     {'4', '5', '6'},
                                     {'7', '8', '9'}};
                for (int i = 0; i < 3; i++) {                               //sbkuch  reset 
                    for (int j = 0; j < 3; j++) {
                        TIC[i][j] = newTIC[i][j];
                        boardmap[i * 3 + j + 1] = newTIC[i][j];
                    }
                }
                playerwin = 0;
                computerwin = 0;
                cout << "NEW GAME STARTING...⚔️⚔️" << endl;
                print(TIC);
            }
        }

        // Final scores
        cout << "PLAYER  WON " << playerwins << " TIMES" << endl;
        cout << "COMPUTER WON " << computerwins << " TIMES" << endl;

        return 0;
    }      //computer game k liye 

    else if(a==2){
        cout<<endl<<"YOU ARE PLAYING WITH ANOTHER PLAYER:----:"<<endl;
          // Tic-Tac-Toe game setup
            char TIC[3][3] = {{'1', '2', '3'}, 
                              {'4', '5', '6'},
                              {'7', '8', '9'}};
            cout << " 🙏🙏 WELCOME 🙏🙏 TO TIC TAC TOE ⚔️(❌ or ⭕)⚔️! " << endl;
            // 2-player game setup
            char player1sign, player2sign;
            cout << "PLAYER 1, CHOOSE 'X' OR 'O': ";
            cin >> player1sign;
            int player1move, player2move;
            int player1win = 0, player2win = 0; // Control game flow
            int player1wins = 0, player2wins = 0; // Keep track of total wins

            // Validate player symbol selection
            while (true) {
                if (player1sign == 'X' || player1sign == 'x') {
                    player1sign = 'X';
                    player2sign = 'O';
                    break;
                } else if (player1sign == 'O' || player1sign == 'o') {
                    player1sign = 'O';
                    player2sign = 'X';
                    break;
                } else {
                    cout << "Invalid input.🤬🤬 Please choose 'X' or 'O': ";
                    cin >> player1sign;
                }
            }
            // Display player symbols
            cout << "SYMBOL FOR PLAYER 1: " << player1sign << endl;
            cout << "SYMBOL FOR PLAYER 2: " << player2sign << endl;
            print(TIC);
            cout << endl;
            cout<<"WARNING! WARNING! WARNING!";
            cout << " PLEASE ENTER THE AVAILABLE NUMBERS FROM 1 TO 9 ONLY, OTHERWISE YOUR TURN WILL BE SKIPPED 👿😈😈 " << endl;
            cout << endl;
            // Map board positions to numbers
            map<int, char> boardmap;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    boardmap[i * 3 + j + 1] = TIC[i][j];
                }
            }
            // Start game loop
            int count = 1; // Start with the game
            while (count != -1) {
                while (player1win != 1 && player2win != 1) {
                    if (player1win == 1 || player2win == 1) {
                        break;
                    }
                    // Player 1's move
                    if (!iswin(TIC, player1win, player2win, boardmap,player1sign,player2sign)) {
                        cout << "PLAYER 1 MOVE (AVAILABLE SPOTS ARE DISPLAYED ON SCREEN): -->  ";
                        cin >> player1move;
         if (player1move >= 1 && player1move <= 9 && boardmap[player1move] != 'X' && boardmap[player1move] != 'O') {
                            boardmap[player1move] = player1sign;
                            TIC[(player1move - 1) / 3][(player1move - 1) % 3] = player1sign;
                            print(TIC);
                        } else {
                            cout << "INVALID MOVE PLAYER 1 🤬🤬 this is the last warning don't do this again" << endl;
                         cin >> player1move;
            if (player1move >= 1 && player1move <= 9 && boardmap[player1move] != 'X' && boardmap[player1move] != 'O') {
                                 boardmap[player1move] = player1sign;
                                 TIC[(player1move - 1) / 3][(player1move - 1) % 3] = player1sign;
                                 print(TIC);
                        }
                    }
                    // Player 2's move
                    if (!iswin(TIC, player1win, player2win, boardmap,player1sign,player2sign)) {
                        if (player1win == 1 || player2win == 1) {
                            break;
                        }
                        cout << "PLAYER 2 MOVE (AVAILABLE SPOTS ARE DISPLAYED ON SCREEN): -->  ";
                         cin >> player2move;
         if (player2move >= 1 && player2move <= 9 && boardmap[player2move] != 'X' && boardmap[player2move] != 'O') {
                            boardmap[player2move] = player2sign;
                            TIC[(player2move - 1) / 3][(player2move - 1) % 3] = player2sign;
                            print(TIC);
                        } else {
               cout << "INVALID MOVE PLAYER 2 🤬🤬 last warning don't do this again" << endl;
             cin >> player2move;
              if (player2move >= 1 && player2move <= 9 && boardmap[player2move] != 'X' && boardmap[player2move] != 'O') {
                                 boardmap[player2move] = player2sign;
                                 TIC[(player2move - 1) / 3][(player2move - 1) % 3] = player2sign;
                                 print(TIC);
                             }
                        }
                    }
                    // Check for a winner or draw
                    iswin(TIC, player1win, player2win, boardmap,player1sign,player2sign);
                    if (player1win == 1 && player2win == 1) {
                        cout << "DRAW! 😳😳" << endl;
                    } else if (player1win == 1) {
                        cout << "PLAYER 1 WON THE GAME 🥳🥳 " << endl;
                        player1wins++;
                    } else if (player2win == 1) {
                        cout << "PLAYER 2 WON THE GAME 🥳🥳" << endl;
                        player2wins++;
                    }
                }
                }
                // Ask to play again
                cout << "DO YOU WANT TO PLAY AGAIN? ENTER -1 TO EXIT OR 1 TO CONTINUE: --> ";
                cin >> count;
                if (count == 1) {
                    // Reset the board and variables
                    char newTIC[3][3] = {{'1', '2', '3'},
                                         {'4', '5', '6'},
                                         {'7', '8', '9'}};
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            TIC[i][j] = newTIC[i][j];
                            boardmap[i * 3 + j + 1] = newTIC[i][j];
                        }
                    }
                    player1win = 0;
                    player2win = 0;
                    cout<<endl;
                    cout<<endl;
                    cout << "NEW GAME STARTING...⚔️⚔️" << endl;
                    print(TIC);
                }
            
            // Display final results
            cout << "PLAYER 1 WON " << player1wins << " TIMES" << endl;
            cout << "PLAYER 2 WON " << player2wins << " TIMES" << endl;
            return 0;
    }
                //player game  k liye 
       
    }
        
        else if(a==3){
            cout << "YOU ARE PLAYING WITH THE UNBEATABLE COMPUTER AI!" << endl;
            // Tic-Tac-Toe game setup
            char TIC[3][3] = {{'1', '2', '3'},
                              {'4', '5', '6'},
                              {'7', '8', '9'}};
            cout << "🙏🙏 WELCOME 🙏🙏 TO TIC TAC TOE ⚔️ (❌ or ⭕) ⚔️! " << endl;
            // Player and AI symbols
            char playersign, AIsign;
            cout << "PLAYER , CHOOSE 'X' OR 'O': ";
            cin >> playersign;
            int row,col;
            // Validate player symbol selection
            while (true) {
                if (playersign == 'X' || playersign == 'x') {
                    playersign = 'X';
                    AIsign = 'O';
                    break;
                } else if (playersign == 'O' || playersign == 'o') {
                    playersign = 'O';
                    AIsign = 'X';
                    break;
                } else {
                    cout << "Invalid input.🤬🤬 Please choose 'X' or 'O': ";
                    cin >> playersign;
                }
            }

            cout << "SYMBOL FOR PLAYER : " << playersign << endl;
            cout << "SYMBOL FOR AI: " << AIsign << endl;

            print(TIC);
            cout << "WARNING: Enter numbers between 1 and 9 only!" << endl;
            //MAPPING OF BOARD POSITIONS TO NUMBERS
            map<int, char> boardmap;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    boardmap[i * 3 + j + 1] = TIC[i][j];
                }
            }
           //MAPPING ENDS HERE 
            int playerwin = 0, AIwin = 0;
            int playerwins = 0, AIwins = 0;
            int playermove, count = 1;
             while (count != -1) {
                        while (playerwin != 1 && AIwin != 1) {
                            if (playerwin == 1 || AIwin == 1) {
                                break;
                            }
                            // Player  move
                            if (!iswin(TIC, playerwin, AIwin, boardmap,playersign,AIsign)) {
                                cout << "PLAYER  MOVE (AVAILABLE SPOTS ARE DISPLAYED ON SCREEN): -->  ";
                                cin >> playermove;
                 if (playermove >= 1 && playermove <= 9 && boardmap[playermove] != 'X' && boardmap[playermove] != 'O') {
                                    boardmap[playermove] = playersign;
                                    TIC[(playermove - 1) / 3][(playermove - 1) % 3] = playersign;
                                    print(TIC);
                                } 
                        else {  
                            cout << "INVALID MOVE PLAYER 🤬🤬 it's last warning don't do this again" << endl;
                            cin >> playermove;
                             if (playermove >= 1 && playermove <= 9 && boardmap[playermove] != 'X' && boardmap[playermove] != 'O') {
                                                boardmap[playermove] = playersign;
                                                TIC[(playermove - 1) / 3][(playermove - 1) % 3] = playersign;
                                                print(TIC);
                                            } 
                                }
                            }
                            // AI move
                            if (!iswin(TIC, playerwin, AIwin, boardmap,playersign,AIsign)) {
                                if (playerwin == 1 || AIwin == 1) {
                                    break;
                                }
                                // Computer's move (AI)
                                int moveAI = findBestMove(TIC, AIsign, playersign);
      cout <<endl<< "AI MOVE (AVAILABLE SPOTS ARE DISPLAYED ON SCREEN): -->  "<<moveAI<<endl;
                                row = (moveAI - 1) / 3;
                                col = (moveAI - 1) % 3;
                                TIC[row][col] = AIsign;
                                boardmap[moveAI] = AIsign;
                                print(TIC);
                                if (iswin(TIC, playerwin, AIwin, boardmap,playersign,AIsign)) {
                                    print(TIC);
                                    cout << "AI wins!" << endl;
                                    break;
                                }
                            }
                        }
                            // // Check for a winner or draw
                            iswin(TIC, playerwin, AIwin, boardmap,playersign,AIsign);
                            if (playerwin == 1 && AIwin == 1) {
                                cout << "DRAW! 😳😳" << endl;
                            }
                            else if (playerwin == 1) {
                                cout << "PLAYER 1 WON THE GAME 🥳🥳 " << endl;
                                playerwins++;
                            }
                            else if (AIwin == 1) {
                                cout << "AI WON THE GAME 🥳🥳" << endl;
                                AIwins++;
                            }
                        
                        // Ask to play again
                        cout << "DO YOU WANT TO PLAY AGAIN? ENTER -1 TO EXIT OR 1 TO CONTINUE: --> ";
                        cin >> count;
                        if (count == 1) {
                            // Reset the board and variables
                            char newTIC[3][3] = {{'1', '2', '3'},           
                                                 {'4', '5', '6'},                //REFERENCE BOARD purane board ko reset kne k liye
                                                 {'7', '8', '9'}};
                            //RESETING GAME BOARD
                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    TIC[i][j] = newTIC[i][j];
                                    boardmap[i * 3 + j + 1] = newTIC[i][j];
                                }
                            }
                            playerwin = 0;
                            AIwin = 0;
                            cout<<endl;
                            cout<<endl;
                            cout << "NEW GAME STARTING...⚔️⚔️" << endl;
                            print(TIC);
                        }
                    }
                    // Display final results
                    cout << "PLAYER 1 WON " << playerwins << " TIMES" << endl;
                    cout << "AI WON " << AIwins << " TIMES" << endl;
                    return 0;
            }
            //if player enter invalid input instead of 1,2 or 3
    else{
                cout<<"INVALID INPUT 🤬🤬";                
        cout<<"PLEASE RUN GAME AGAIN ENTER 1 , 2  or 3 ONLY"<<endl;
     }
}



// game  completed 