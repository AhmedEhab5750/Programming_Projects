# Purpose: The game is designed to take input from two players (First Player and Second Player)
# it adds numbers from both sides to total_sum till one of them adds a number that makes the total_sum be 100 or more
def game_100():
    # Started with declaring the variables to make them in a bigger scope.
    first_player = 0
    second_player = 0
    total_sum = int(0)
    while total_sum < 100:
        # Using try and except to handle the error of entering a non integer number.
        try:
            print(f"current Total Sum is: {total_sum}")
            # If an error occurred in the first or second player input we will restart the round.
            # When restarting the round we need to make sure that we removed what happened in it.
            first_is_added = 0
            min_num = min(10, (100 - total_sum))
            first_player = int(input(f"First player enter a number from 1 to {min_num}: "))
            # next while loop will only work when the input from First Player is less than 1 or
            # more than minimum of 10 and (100 - total_sum)
            while not 1 <= first_player <= min_num:
                print("Invalid input entered from first player ", end='')
                print(f"make sure to input a number from 1 to {min_num}.")
                first_player = int(input(f"First player enter a number from 1 to {min_num}: "))
            total_sum += first_player
            first_is_added = 1
            # the next condition is to know if the First Player won after adding his input to the total_sum or not.
            if total_sum == 100:
                print("Congratulations! First player won.")
                break
            min_num = min(10, (100 - total_sum))
            print(f"current Total Sum is: {total_sum}")
            second_player = int(input(f"Second player enter a number from 1 to {min_num}: "))
            # next while loop will only work when the input from Second Player is less than 1 or
            # more than minimum of 10 and (100 - total_sum)
            while not 1 <= second_player <= min_num:
                print("Invalid input entered from second player make ", end='')
                print(f"sure to input a number from 1 to {min_num}.")
                second_player = int(input(f"Second player enter a number from 1 to {min_num}: "))
            total_sum += second_player
            # the next condition is to know if the Second Player won after adding his input to the total_sum or not.
            if total_sum == 100:
                print("Congratulations! Second player won.")
                break
        # We make the exception in error to print it to the Players.
        except Exception as error:
            # If first_is_added equal 1 then that means that the error is from The Second Player.
            # Which means that we need to remove The First Player's input from the total_sum.
            # If first_is_added equal 0 we continue because the error occurred from The First Player.
            if first_is_added == 1:
                total_sum -= first_player
            print(f"Invalid input {error} entered from a player. restarting the round.")


print("This is 100 game.")
print("The game is designed to take input from two players (First Player and Second Player)", end='')
print("it adds numbers from both sides to total_sum till one of ", end='')
print("them adds a number that makes the total_sum equal 100 and that means that he won")
print("_______________________________________________________________________________________________________________")
print("")
while 1:
    # I'm using .lower() built-in function to handle uppercased inputs (e.g. sTart, STart, START, ...etc)
    choice = input("Welcome in 100GAME. Type 'Start' to start a new game. or type 'Quit' to quit. \n").lower()
    if choice == "start":
        game_100()
    # If The Players entered 'quit' we terminate the program.
    elif choice == "quit":
        break
    # This else is to handle the case that the user enters something else other than start or quit.
    else:
        print(f"'{choice}' Is an invalid choice. Enter one of the two choices.")
        continue