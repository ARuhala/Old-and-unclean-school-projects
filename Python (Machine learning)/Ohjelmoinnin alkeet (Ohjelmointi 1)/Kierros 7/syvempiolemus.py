dict = { "a":4, "b":1, "c":5, "e":3 }
dict["d"] = 2
dict["a"] = 6
for x in sorted(dict):
    print(x, dict[x])