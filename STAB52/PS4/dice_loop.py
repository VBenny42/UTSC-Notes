list = []

for i in range(6):
    print("----------------------")
    for j in range(6):
        list.append(i+j+2)

for i in range(2, 13):
    print(i, list.count(i))