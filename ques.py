# given number , take input from user, second largest prime number


def checkPrime(num: int):
    for i in range(2, num):  # 2 to the number-1
        if num % i == 0:
            return False
    return True


def secondLargestPrime(input: int) -> int:
    count = 0
    for i in range(input, 0, -1):
        if checkPrime(i):
            count += 1
            if count == 2:
                return i
    return -1


# driver

input = int(input("Enter a number:"))
res = secondLargestPrime(input)
print("Result is : ", res)
