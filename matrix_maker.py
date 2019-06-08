import random
with open("matrix.txt", "w") as f:
    for i in range(20):
        for j in range(20):
            if i < 5:
                f.write(str(random.randint(15,25)) + ", ")
            elif i < 10:
                f.write(str(random.randint(25, 40)) + ", ")
            elif i < 15:
                f.write(str(random.randint(60, 80)) + ", ")
            else:
                f.write(str(random.randint(80, 100)) + ", ")
        f.write("\n")