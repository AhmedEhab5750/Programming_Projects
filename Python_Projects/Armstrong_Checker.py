def armstrong_checker():
    try:
        number = int(input("Enter a number: "))
        number = str(number)
        digits = [int(char) for char in number]
        num_size = len(digits)
        result = 0
        for i in range(num_size):
            result += (digits[i] ** num_size)
        if result == int(number):
            print("The number is an Armstrong number")
        else:
            print("The number is not an Armstrong number")
    except Exception as Error:
        print(f"{Error} Invalid input entered, try again")


while True:
    armstrong_checker()
