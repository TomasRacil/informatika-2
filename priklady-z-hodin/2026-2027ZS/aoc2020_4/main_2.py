import re
from os.path import realpath, dirname, join

def read_paragraphs(file):
    block = []
    for line in file:
        if line.strip() == "":
            if block:
                yield "".join(block)
                block = []
        else:
            block.append(line)
    if block:
        yield "".join(block)


with open(join(dirname(realpath(__file__)),"data.txt"), 'r', encoding='utf-8') as f:
    pocitadlo_1 = 0
    pocitadlo_2 = 0
    
    regex_1 = re.compile(
        r"(?=.*\bbyr:)"
        r"(?=.*\biyr:)"
        r"(?=.*\beyr:)"
        r"(?=.*\bhgt:)"
        r"(?=.*\bhcl:)"
        r"(?=.*\becl:)"
        r"(?=.*\bpid:)",
        re.DOTALL,
    )
    regex_2 = re.compile(
        r"(?=.*\bbyr:(?:19[2-9][0-9]|200[0-2])(?!\S))"
        r"(?=.*\biyr:(?:201[0-9]|2020)(?!\S))"
        r"(?=.*\beyr:(?:202[0-9]|2030)(?!\S))"
        r"(?=.*\bhgt:(?:(?:1[5-8][0-9]|19[0-3])cm|(?:59|6[0-9]|7[0-6])in)(?!\S))"
        r"(?=.*\bhcl:(?:#[0-9a-f]{6})(?!\S))"
        r"(?=.*\becl:(?:amb|blu|brn|gry|grn|hzl|oth)(?!\S))"
        r"(?=.*\bpid:(?:[0-9]{9})(?!\S))",
        re.DOTALL,
    )
    
    for block in read_paragraphs(f):
        if re.match(regex_1,block.strip()):
            pocitadlo_1+=1
            if re.match(regex_2, block.strip()):
                pocitadlo_2+=1
        
        
    print(pocitadlo_1)
    print(pocitadlo_2)
