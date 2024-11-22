def compress(text):
    out = ""
    n = 1
    for i in range(len(text) - 1):
        if text[i] == text[i+1]:
            n+=1
        elif text[i] != text[i+1] and n != 1:
            out += f"{n}{text[i]}"
            n = 1
            