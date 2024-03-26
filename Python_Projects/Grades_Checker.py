
def grades_1():
    try:
        mark = int(input("Enter Your Mark: "))
        while not 0 <= mark <= 100:
            print(f"Invalid input. {mark} is out of the range enter a right mark")
            mark = int(input("Enter Your Mark: "))
        if 90 <= mark <= 100:
            print("A+")
        elif 85 <= mark < 90:
            print("A")
        elif 80 <= mark < 85:
            print("B+")
        elif 75 <= mark < 80:
            print("B")
        elif 70 <= mark < 75:
            print("C+")
        elif 65 <= mark < 70:
            print("C")
        elif 60 <= mark < 65:
            print("D+")
        elif 50 <= mark < 60:
            print("D")
        else:
            print("F")
    except Exception as Error:
        print(f"{Error} Invalid input entered, try again")


while True:
    grades()