from os.path import dirname, join, realpath

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

def process_seed_1(seed:int, rules:list, reverse:bool = False)->int:
    for layer in (rules if not reverse else rules[::-1]):
        for ran in layer:
            if not reverse:
                if seed>=ran[1] and seed < ran[1]+ran[2]:
                    seed = seed + (ran[0]-ran[1])
                    break
            else:
                if seed>=ran[0] and seed < ran[0]+ran[2]:
                    seed = seed + (ran[1]-ran[0])
                    break
    return seed

def load_data(file_name:str)->tuple:
    with open(
            join(dirname(realpath(__file__)), file_name), "r", encoding="utf-8"
        ) as file:
            paragraphs = read_paragraphs(file)
            seeds = tuple(map(int, next(paragraphs).split()[1:]))
            intervals = [
                    [tuple(map(int, ran.split()))
                    for ran in paragraph.strip().split("\n")[1:]
                    ] 
                for paragraph in paragraphs
            ]
            return (seeds, intervals)

def find_border_points(rules:list)->set[tuple[int,int]]:
    border_points = set()
    for idx,layer in enumerate(rules):
        for ran in layer:
            for point in (ran[1], ran[1] + ran[2]):
                start_mapping = process_seed_1(point,rules[:idx],True)
                end_mapping = process_seed_1(point, rules[idx:])
                border_points.add((start_mapping,end_mapping))
    return border_points        

def solve_brute_force(seed_ranges:list[range], intervals:list)->int:
    smallest = None
    for ran in seed_ranges:
        for seed in ran:
            result = process_seed_1(seed, intervals)
            if smallest is None or result < smallest:
                smallest = result
    return smallest

def solve_border_points(seed_ranges:list[range], intervals:list)->int:
    border_points = sorted(find_border_points(intervals), key=lambda x: x[0])
    smallest = None
    for ran in seed_ranges:
        candidates = {process_seed_1(ran.start, intervals)}
        for start, end in border_points:
            if start in ran:
                candidates.add(end)
        ran_smallest = min(candidates)
        if smallest is None or ran_smallest < smallest:
            smallest = ran_smallest
    return smallest

def main():
    seeds, intervals = load_data("test.txt")
    seed_ranges_1 = [range(seed, seed + 1) for seed in seeds]
    seed_ranges_2 = [range(seeds[i], seeds[i] + seeds[i + 1]) for i in range(0, len(seeds), 2)]

    # Verze 1
    # print(solve_brute_force(seed_ranges_1, intervals))
    # print(solve_brute_force(seed_ranges_2, intervals))

    # Verze 2
    print(solve_border_points(seed_ranges_1, intervals))
    print(solve_border_points(seed_ranges_2, intervals))
        
        
        
        
if __name__ =="__main__":
    main()