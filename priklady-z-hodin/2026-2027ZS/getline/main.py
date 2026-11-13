from os.path import realpath, dirname, join

def getline(file, separtator="\n"):
    with open(file, 'r', encoding='utf-8') as f:
        block = []
        for line in f:
            for char in line:
                if char != separtator:
                    block.append(char)
                else:
                    yield "".join(block)
                    block.clear()
                


file_path = join(dirname(realpath(__file__)),"test.txt")
for block in getline(file_path, ";"):
    print(block.strip())