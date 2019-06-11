import random
with open("matrix.txt", "w") as f:
    for i in range(1000):
        for j in range(1000):
            if i == 0 or j ==0 or i==999 or j == 999:
                f.write(str(100) + ",")
            elif i < 200:
                f.write(str(random.randint(15,25)) + ",")
            elif i < 400:
                f.write(str(random.randint(25, 40)) + ",")
            elif i < 700:
                f.write(str(random.randint(60, 80)) + ",")
            else:
                f.write(str(random.randint(80, 100)) + ",")

        f.write("\n")