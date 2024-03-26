def list_sort(input_list):
    n = len(input_list)
    for i in range(n):
        for j in range(0, n - i - 1):
            if input_list[j] > input_list[j + 1]:
                temp = input_list[j]
                input_list[j] = input_list[j + 1]
                input_list[j + 1] = temp


def list_compare():
    try:
        list1 = input("Enter a list of numbers starting with '[' separated by ',' and ended with ']'\n")
        numbers_list1 = [int(char) for char in list1[1:-1].split(',')]
        list_sort(numbers_list1)
        list2 = input(
            "Enter another list of numbers starting with '[' numbers are separated by ',' and ended with ']'\n")
        numbers_list2 = [int(num) for num in list2[1:-1].split(',')]
        list_sort(numbers_list2)
        if numbers_list1 == numbers_list2:
            print("Lists are equal = True")
        else:
            print("Lists are equal = False")
    except Exception as Error:
        print(f"{Error}Invalid input!.")
        print("Please enter the input in the correct format (example: [0, 0, 0, 0, 0, 0, 0, 0]). ", end='')
        print("Restarting the program")


while True:
    list_compare()
