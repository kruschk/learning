#!/usr/bin/python3

# display our inventory
def display_inventory(inv):
    print("Inventory:")
    total_items = 0;
    for k, v in inv.items():         # for each key and value in our inventory
        print(str(v) + " " + str(k)) # print the count (value), then the key
        total_items += v             # add the count to the total
    print("Total number of items: " + str(total_items))

# add loot, represented as a list, to our inventory
def add_to_inventory(inv, loot):
    for item in loot:           # loop through each item in the loot list
        inv.setdefault(item, 0) # if the item isn't in our inventory, add it
        inv[item] += 1          # increment the count

# dictionary for our initial inventory
inventory = {
        "rope": 1,
        "torch": 6,
        "gold coin": 42,
        "dagger": 1,
        "arrow": 12
}

# loot to add to the inventory
dragon_loot = ["gold coin", "dagger", "gold coin", "gold coin", "ruby"]

# display, add loot, then display again
display_inventory(inventory)
add_to_inventory(inventory, dragon_loot)
display_inventory(inventory)
