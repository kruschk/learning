def hexToDec():

    # Get a hexadecimal input from the user and reverse it.
    hex_in = input("Please enter a hexadecimal number: ").upper()
    if not hex_in.isalnum():
        print("Invalid input! Please try again.")
        hexToDec()
        return
    hex_in = hex_in[::-1]

    # Initialize variables.
    hex_list = []
    dec_out = 0
    idx = 0

    # Append each character of the hexadecimal input to a new list, hex_list.
    for symbol in hex_in:
        if symbol.isalpha():
            if symbol == 'A':
                hex_list.append(int(10))
            elif symbol == 'B':
                hex_list.append(int(11))
            elif symbol == 'C':
                hex_list.append(int(12))
            elif symbol == 'D':
                hex_list.append(int(13))
            elif symbol == 'E':
                hex_list.append(int(14))
            elif symbol == 'F':
                hex_list.append(int(15))
            else:
                print("Please ensure your number only uses characters from 0 - 9 and A - F inclusive.")
                hexToDec()
                return
        else:
            hex_list.append(int(symbol))

    # Loop through hex_list, multiplying each number by 16 to the power of its index.
    while idx < len(hex_list):
        dec_out += hex_list[idx]*16**(idx)
        idx += 1

    # Print and return result.
    print("In decimal form, that number is equivalent to: %d" % dec_out)
    return dec_out

hexToDec()
