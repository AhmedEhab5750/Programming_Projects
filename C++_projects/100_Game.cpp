/*
// Program: This is 100 game.
            The game is designed to take input from two players (First Player and Second Player)
            it adds numbers from both sides to total_sum till one of them adds a number that
            makes the total_sum be 100.
// Date: 21/2/2024 "I made Version 1 of it after doing it in python directly"
// Last_Update: 1/3/2024 "I made it better by using integer 'mini' and some other features in the code"
// Version: 2.0
 */
#include <bits/stdc++.h>
using namespace std;
int main(){
    cout << "This is 100 game.\n";
    cout << "The game is designed to take input from two players (First Player and Second Player)\n";
    cout << "The game adds numbers from both sides to total_sum till one of ";
    cout << "them adds a number that makes the total_sum equal 100 and that means that he won\n";
    cout << "_______________________________________________________________________________________________\n";
    while(true){
        string choice;
        cout << "Welcome in 100GAME. Type 'Start' to start a new game. or type 'Quit' to quit.\n";
        cin >> choice;
        int first_player, second_player, total_sum = 0, mini = INT_MAX;
        // Next for loop to change the input to lower case using tolower to change each character.
        for (auto &c : choice){
            c = tolower(c);
        }
        if(choice == "start"){
            // While the total_sum doesn't exceed 100 the game continues
            while(total_sum < 100){
                cout << "Current total_sum is: " << total_sum << '\n';
                // 'mini' Is used to make the user enter a number from 1 to mini which is 10 or lower.
                mini = min(10, (100 - total_sum));
                cout << "First player enter a number from 1 to " << mini << '\n';
                cin >> first_player;
                /*
                 * Next for loop for wrong input and using cin.fail(), cin,clear(),
                 * cin.ignore(numeric_limits<streamsize>::max(), '\n') to remove all wrong input from the buffer that
                 * holds the input.
                 */
                while (cin.fail() || first_player < 1 || first_player > mini) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input entered from first player make sure to input a number from 1 to " << mini << '\n';
                    cout << "First player enter a number from 1 to " << mini << '\n';
                    cin >> first_player;
                }
                // Updating total_sum.
                total_sum += first_player;
                // Checking if the First Player won or not.
                if (total_sum == 100){
                    cout << "Congratulations! First player won." << endl;
                    break;
                }
                mini = min(10, (100 - total_sum));
                cout << "Current total_sum is: " << total_sum << '\n';
                cout << "Second player enter a number from 1 to " << mini << '\n';
                cin >> second_player;
                /*
                 * Next for loop for wrong input and using cin.fail(), cin,clear(),
                 * cin.ignore(numeric_limits<streamsize>::max(), '\n') to remove all wrong input from the buffer that
                 * holds the input.
                 */
                while (cin.fail() || second_player < 1 || second_player > mini){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input entered from Second player make sure to input a number from 1 to " << mini << '\n';
                    cout << "Second player enter a number from 1 to " << mini << '\n';
                    cin >> second_player;
                }
                // Updating total_sum.
                total_sum += second_player;
                // Checking if the Second Player won or not.
                if (total_sum == 100){
                    cout << "Congratulations! Second player won." << endl;
                    break;
                }
            }
        }
        // If The Players entered 'quit' we terminate the program.
        else if(choice == "quit"){
            break;
        }
        // This else is to handle the case that the user enters something else other than start or quit.
        else{
            cout << '{' << choice << "} Is an invalid choice. Enter one of the two choices.\n";
            continue;
        }
    }
    return 0;
}
