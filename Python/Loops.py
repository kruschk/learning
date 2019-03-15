def remove_duplicates(list_in):
    list_out = []
    for i in range(len(list_in)):
        if list_in[i] not in list_out:
            list_out.append(list_in[i])
        else:
            continue
    return list_out

print(remove_duplicates(["string", "string", "another string", 2, 3, 2]))
