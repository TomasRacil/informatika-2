import re
from os.path import realpath, dirname, join

with open(join(dirname(realpath(__file__)),"data.txt"), 'r', encoding='utf-8') as f:
    data = f.read()

regex_1 = re.compile(
    r"(?:\A|\n\s*\n)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bbyr:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\biyr:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\beyr:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bhgt:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bhcl:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\becl:)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bpid:)"
    r"(\S[\s\S]*?)"
    r"(?=\n\s*\n|\Z)"
)

platne_pasy = regex_1.findall(data)
print(f"Pasy se 7 povinnými poli: {len(platne_pasy)}")

regex_2 = re.compile(
    r"(?:\A|\n\s*\n)"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bbyr:(?:19[2-9][0-9]|200[0-2])(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\biyr:(?:201[0-9]|2020)(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\beyr:(?:202[0-9]|2030)(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bhgt:(?:(?:1[5-8][0-9]|19[0-3])cm|(?:59|6[0-9]|7[0-6])in)(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bhcl:#[0-9a-f]{6}(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\becl:(?:amb|blu|brn|gry|grn|hzl|oth)(?!\S))"
    r"(?=(?:(?!\n\s*\n)[\s\S])*?\bpid:[0-9]{9}(?!\S))"
    r"(\S[\s\S]*?)"
    r"(?=\n\s*\n|\Z)"
)

platne_pasy = regex_2.findall(data)
print(f"Počet platných pasů: {len(platne_pasy)}")