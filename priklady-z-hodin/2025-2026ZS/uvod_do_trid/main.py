from student import Student

def funkce():
    """
    Docstring for funkce
    """
    pass

def main():
    s1 = Student("Jakub", 4, [1,2,3,4])
    print(s1.prumer())
    s1.znamka = 4
    print(s1.znamka)
    print(s1.prumer())

if __name__ == "__main__":
    main()