import numpy as np
import csv
from sys import exit
from enum import Enum

# Constants
MAX_AGE = 28
MIN_AGE = 18
question = {
    1: "Hvilket kjønn er du? [m/f/bi]: ",
    2: "Hvor gammel er du?: ",
    3: "Tar du et eller flere fag? [ja, nei]: ",
    4: "Tar du ITGK? [ja, nei]: ",
    5: "Hvor mange timer bruker du daglig (i snitt) på lekser?: "
}


class Person():
    def __init__(self):
        self.sex: str       = None
        self.age: int       = None
        self.subject: bool  = None
        self.itgk: bool     = None
        self.hours: int     = None
    
    def format_person_data(self):
        return [self.sex, self.age, self.subject, self.itgk, self.hours]
        
    def ask_sex(self):
        condition = False
        while not condition:
            user_input = input(question[1]) 
            close_condition(user_input)
            user_input = user_input.lower()
            if user_input == "m" or user_input == "f" or user_input == "bi":
                self.sex = user_input
                condition = True
    
    def ask_age(self) -> bool:
        condition = False
        while not condition:
            user_input = input(question[2]) 
            close_condition(user_input)
            user_input = int(user_input)
            if MAX_AGE >= user_input >= MIN_AGE:
                self.age = user_input
                condition = True # not needed, too paranoid to delete
                return True
            elif user_input >= MAX_AGE:
                print("Du er desverre for gammel til å delta.")
                return False
            elif user_input <= MIN_AGE:
                print("Du er desverre for ung til å delta.")
                return False
             

    def ask_subject(self):
        condition = False
        while not condition:
            user_input = input(question[3]) 
            close_condition(user_input)
            user_input.lower()
            if user_input == "ja":
                self.subject = True
                condition = True
            elif user_input == "nei":
                self.subject = False
                condition = True
    
    def ask_itgk(self):
        condition = False
        while not condition:
            user_input = input(question[4]) 
            close_condition(user_input)
            user_input = user_input.lower()
            if user_input == "ja":
                self.itgk = True
                condition = True
            elif user_input == "nei":
                self.itgk = False
                condition = True
    
    def ask_hours(self):
        condition = False
        while not condition:
            user_input = input(question[5]) 
            close_condition(user_input)
            user_input = float(user_input)
            if 0 <= user_input <= 24:
                self.hours = user_input
                condition = True

                
def close_condition(input) -> None:
    if input.lower() == "hade":
        close()
        

# if current_state == State.CLOSE run this functino
# TODO: Build function
def close() -> None:
    """
    Closing sequence for the program.  
    """

    with open("data.csv", mode="r") as file:
        reader = csv.reader(file, delimiter=";")
        prev_data = [row for row in reader]
        
    new_data = prev_data + current_data

    print(f"New data: {new_data}")
    print(f"Current data: {current_data}")

    print("Saving new data...")
    with open("data.csv", mode="w", newline="") as file:
        writer = csv.writer(file, delimiter=";")
        writer.writerows(new_data)
        print("Data saved successfully!")
    print("Closing program...")
    exit()

print("############################# NY KJØRING AV KODE #############################")
current_data = []
len_data = len(current_data)
while True:
    print("------------------ NY SPØRRE RUNDE ------------------")

    person = Person()
    person.ask_sex()
    if not person.ask_age(): # ask_age returns False if condition is not met. 
        print("Data ikke lagret.")
        continue
    person.ask_subject()
    person.ask_itgk()
    person.ask_hours()
    
    try:
        current_data.append(person.format_person_data())
        print("User data saved...")
        print("Thank you!")
    except EnvironmentError as e:
        print(f"Problem storing user data: {e}")
