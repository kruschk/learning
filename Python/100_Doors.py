import time

start = time.clock()
door_initial = [0 for x in range(100)] # 0 will indicate closed, 1 will indicate open

def toggle(list_in, incr):
    # returns a list containing the opposite of whatever was in the list (0 or 1) for each increment.
    i = incr - 1
    while i < len(list_in):
        if list_in[i] == 0:
            list_in[i] = 1
            i += incr
        else:
            list_in[i] = 0
            i += incr
    return list_in

def step(list_in):
    # loops through and calls toggle(list_in, incr) as many times as is necessary
    list_out = list_in
    j = 1
    while j <= len(list_in):
        list_out = toggle(list_out, j)
        j += 1
    return list_out

final = (step(door_initial))

def conversion(list_in):
    list_out = []
    for k in range(len(list_in)):
        if list_in[k] == 1:
            list_out.append(k + 1)
            k += 1
        else:
            k += 1
            continue
    return list_out

print(conversion(final))
end = time.clock()

print(end - start)
