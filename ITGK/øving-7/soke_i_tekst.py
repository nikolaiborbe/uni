import re


def read_from_file(filename):
    with open(filename, "r") as file:
        for line in file:
            print(remove_symbols(line))


def remove_symbols(text):
    text = text.lower()
    return re.sub(r"[^A-Za-z0-9\s]+", "", text)


def count_words(filename):
    count_words = {}
    words = []
    with open(filename, "r") as file:
        for line in file:
            clean_line = remove_symbols(line)
            clean_words = clean_line.split()
            for word in clean_words:
                words.append(word)
    for word in words:
        if word not in count_words:
            count_words[word] = 1
        elif word in count_words:
            count_words[word] += 1

    return count_words


print(count_words("alice.txt"))
