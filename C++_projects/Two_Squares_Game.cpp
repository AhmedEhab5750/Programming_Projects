/*
// Program : This is the third game that is called two squares.
    the game is about that there are 2 players that every one of them
    choose 2 adjacent numbers that weren't chosen yet and the last player that played a valid
    play wins the game. */
// Version : 3.0
// Date : 1/3/2024
#include <bits/stdc++.h>
using namespace std;
// Next map is to translate every square's number to its location in the 2D array.
map <int,pair<int,int>> locations = {
        {1, {0, 0}},
        {2, {0, 1}},
        {3, {0, 2}},
        {4, {0, 3}},
        {5, {1, 0}},
        {6, {1, 1}},
        {7, {1, 2}},
        {8, {1, 3}},
        {9, {2, 0}},
        {10, {2, 1}},
        {11, {2, 2}},
        {12, {2, 3}},
        {13, {3, 0}},
        {14, {3, 1}},
        {15, {3, 2}},
        {16, {3, 3}}
};
// The next function is to check for the input if they are valid or not and isa it handles all possible inputs.
void is_valid_input(int &num1, int &num2, map <int,int> sq, bool player){
    // cin.fail() to handle if the user entered a non integer value.
    while(cin.fail() || ((max(num1, num2) - min(num1, num2) != 4 && max(num1, num2) - min(num1, num2) != 1) || (num1 > 16 || num1 < 1 || num2 > 16 || num2 < 1) || sq[num1] == 1 || sq[num2] == 1) || (min(num1,num2) == 4 && max(num1,num2) == 5) || (min(num1,num2) == 8 && max(num1,num2) == 9) || (min(num1,num2) == 12 && max(num1,num2) == 13)){
        // Using cin.clear() to clear the current cin from any string that might break the program.
        // using cin.ignore() to ignore the next \n that the player wrote to send the wrong answer.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        num1 = 0;
        num2 = 0;
        cout << "Invalid input from Player " << ((player) ? 1 : 2) << " Please enter 2 adjacent numbers that haven't been chosen yet\n";
        cin >> num1 >> num2;
    }
}
void two_squares() {
    // This is the main 2D array that we change values in it.
    string game[4][4] = {
            {"1",  "2",  "3",  "4"},
            {"5",  "6",  "7",  "8"},
            {"9",  "10", "11", "12"},
            {"13", "14", "15", "16"}
    };
    // Next deque is used to check the winner in last 3 moves.
    deque<int> sq_left;
    // Next map is for checking if the value is used or not.
    map<int, int> sq = {
            {1,  0},
            {2,  0},
            {3,  0},
            {4,  0},
            {5,  0},
            {6,  0},
            {7,  0},
            {8,  0},
            {9,  0},
            {10, 0},
            {11, 0},
            {12, 0},
            {13, 0},
            {14, 0},
            {15, 0},
            {16, 0}
    };
    // Next bool is to change the player from 1 to 2 and vice versa.
    bool player = true;
    // Next counter is to calculate rounds from 1 to 8 because last 3 rounds got special conditions in my code.
    int counter = 0;
    // Now entering the loop that the player rounds continue in it till it's done.
    while (true) {
        // can_play to check in some special conditions starting from round 6 to check if the player got valid moves or not.
        int can_play = 0;
        // Increasing the counter to count the current round.
        counter++;
        int num1, num2;
        // Printing the 2D array to show the players the current game state.
        for (auto &i: game) {
            for (auto &j: i) {
                cout << j << setw(3);
            }
            cout << '\n';
        }
        // Telling the current player to enter 2 adjacent numbers that aren't used yet.
        cout << "Player " << ((player) ? 1 : 2) << " Please enter 2 adjacent numbers that haven't been chosen yet\n";
        cin >> num1 >> num2;
        // Checking whether they are valid or not using the function that we made earlier.
        is_valid_input(num1, num2, sq, player);
        // Changing the map values to say that the value is used now.
        sq[num1] = 1;
        sq[num2] = 1;
        // Using the map that we did earlier to change the squares that the user chose
        // from the 2D array 'game' to 'X'.
        game[locations[num1].first][locations[num1].second] = "X";
        game[locations[num2].first][locations[num2].second] = "X";
        // Those conditions will start working in last 3 rounds 6 7 8 that we are expecting a winner in one of them.
        if(counter > 5){
            // If it's 8 that means that we already used all numbers so the current player won because the other one
            // don't have any 2 numbers to choose from.
            if(counter == 8){
                cout << "Player " << ((player) ? 1 : 2) << " won!\n";
                break;
            }
                // If we are in round 7 we might find that there are no 2 valid values to choose from that is why we are checking it.
            else if(counter == 7){
                // Clearing sq_left to know what is left now.
                sq_left.clear();
                // Checking what is left by moving in all the map that I made to assign used values by 1 in it.
                for(int i = 1;i <= 16;i++){
                    if(sq[i] == 0){
                        sq_left.push_back(i);
                    }
                }
                // Doing this condition that isa checks all possible conditions that if it happens that means the current player won.
                if(max(sq_left.front(), sq_left.back()) - min(sq_left.front(), sq_left.back()) != 1 && max(sq_left.front(), sq_left.back()) - min(sq_left.front(), sq_left.back()) != 4 ){
                    cout << "Player " << ((player) ? 1 : 2) << " won!\n";
                    return;
                }
            }
                // This else is because we might find out that there are 4 values left but every one of them isn't valid
                // with any other value.
            else{
                // Clearing sq_left.
                sq_left.clear();
                // Checking for what is left.
                for(int i = 1;i <= 16;i++){
                    if(sq[i] == 0){
                        sq_left.push_back(i);
                    }
                }
                // Resetting can_play to zero before going in the loop.
                can_play = 0;
                // The next nested loop checking if there are any 2 valid values or not if it found 2 valid adjacent numbers
                // it breaks and make can_play = 1 and continue the game else that means no valid numbers so the current win.
                for(auto k : sq_left){
                    for(auto l : sq_left){
                        if(max(k, l) - min(k, l) == 1 || max(k, l) - min(k, l) == 4){
                            can_play = 1;
                            break;
                        }
                    }
                    if(can_play == 1){
                        break;
                    }
                }
                // If can_play we just continue else we say that the current player that chose the last 2 numbers win.
                if(can_play == 1){
                    can_play = 0;
                    continue;
                }
                else{
                    cout << "Player " << ((player) ? 1 : 2) << " won!\n";
                    return;
                }
            }
        }
        // Changing the current player.
        player = !player;
    }
}
int main() {
    while(true){
        cout << "-------------------------------------------------------------------------------------\n";
        cout << "Welcome in Two Squares Game.\nThe game is about a 2D array that got squares named from 1 to 16.\n";
        cout << "Two players play it every player in his round should choose 2 valid adjacent numbers that weren't chosen yet.\n";
        cout << "-------------------------------------------------------------------------------------\n";
        string choice;
        cout << "Please Enter 'start' to start playing and 'quit' to quit the program\n";
        cin >> choice;
        for(auto &k : choice){
            k = tolower(k);
        }
        if(choice == "start"){
            two_squares();
        }
        else if(choice == "quit"){
            break;
        }
        else{
            cout << "Invalid choice. Restarting the program\n";
        }
    }
    return 0;
}
