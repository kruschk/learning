def fib_n_mod_d(tests):
    numbers = raw_input().split()
    answer = []

    for test in range(tests):
        a, b, c = 0, 1, 0
        for count in range(int(max(numbers))):
            c = a + b
            if c%int(numbers[test]) == 0:
                answer.append(str(count+2))
                break
            a = b
            b = c
    print(" ".join(answer))

fib_n_mod_d(input())