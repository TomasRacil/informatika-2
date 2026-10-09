# import copy

# def pridej_opravneni(profil:dict, opravneni:str, role=None)->dict:
#     if role==None:
#         role=[]
#     role.append(opravneni)
#     profil["role"]=role
#     return profil


def klonuj_a_uprav_profil(puvodni_profil:dict, nova_data:dict)->dict:
    # kopie = copy.deepcopy(puvodni_profil)
    # kopie = puvodni_profil.copy()
    # for k, v in nova_data.items():
    #     kopie[k]=v
    # kopie = {k:v for k,v in puvodni_profil.items()}
    # for k, v in nova_data.items():
    #     kopie[k]=v
    # return kopie

    return {k: 
            nova_data[k] if k in nova_data else v 
            for k,v 
            in puvodni_profil.items()}

p1 = {"jmeno": "Jan", "prava": ["read", "write"]}
# p2 = pridej_opravneni(p1, "write")
# p3 = pridej_opravneni(p2, "execute")
# print(p1)
# print(p2)
# print(p3)

kopie = klonuj_a_uprav_profil(p1, {"jmeno": "Petr", "prava": ["admin"]})
print("Původní:", p1)
print("Kopie:", kopie)

