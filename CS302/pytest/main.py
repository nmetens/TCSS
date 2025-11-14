
try:
    x = int(input("Enter a value > 10: "))
    assert x > 10 
        
except:
    print("There was an exception.")
else:
    print("Success")
