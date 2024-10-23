# a
my_family = {}

# b
def add_family_member(rolle, navn):
    my_family[rolle] = navn

add_family_member('bror', 'Arne')
print (my_family)
add_family_member('far', 'Bob Bernt')
print (my_family)

# c
my_family = {}
def add_family_member_v2(rolle, navn):
    if rolle not in my_family:
        my_family[rolle] = [navn]
    elif rolle in my_family:
        my_family[rolle].append(navn)

add_family_member_v2('bror', 'Arne')
add_family_member_v2('mor', 'Anne')
add_family_member_v2('bror', 'Geir')
print (my_family)
