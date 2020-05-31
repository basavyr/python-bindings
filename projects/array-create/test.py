import retarray as x

n = 100
init = 3
y = x.return_array(n, init)
y1 = x.select_array(n, init, 30, 69)

for id in y:
    local1 = int(id)
    local2 = int(id)+1
    print(local1, local2)
