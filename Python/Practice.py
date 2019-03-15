originalList = [1, 3, 5, 2, 6, 3]

newList = originalList

for i in range(6):
    print(newList[i])
    print(originalList[i])
    newList.remove(newList[i])

print(newList)
