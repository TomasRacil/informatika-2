from muj_balicek import Kurz, Student

if __name__ == "__main__":
    python_kurz = Kurz("IT101", "Programování v Pythonu", kapacita=2)
    java_kurz = Kurz("IT102", "Java pro začátečníky", kapacita=10)

    s1 = Student("Novák", 12345)
    s2 = Student("Svoboda", 67890)
    s3 = Student("Dvořák", 11111)

    s1.zapis_kurz(python_kurz)
    s1.zapis_kurz(python_kurz)
    s2.zapis_kurz(python_kurz)
    s3.zapis_kurz(python_kurz) 
    

    s1.udel_znamku(python_kurz, 1)
    s2.udel_znamku(python_kurz, 3)
    s3.udel_znamku(python_kurz, 1)
    s1.udel_znamku(python_kurz, 8)
    s1.udel_znamku(java_kurz, 1)

    print(s1)
    print(s2)
    print(s3)
    
    print(f"\nStav kurzu: {python_kurz}")
    print(f"\nStav kurzu: {java_kurz}")
    