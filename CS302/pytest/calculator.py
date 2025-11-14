
def print_message(message: str) -> str:
    output: str = "Message: " + message
    print(output)
    return output

def add(a: int, b:int) -> int:
    if a < 0 or b < 0:
        return 0
    return a + b

class Person():
    def __init__(self, name: str = "name", age: int = 1):
        self.name = name
        self.age = age

    def get_name(self):
        return self.name

    def get_age(self):
        return self.age

def main():

    print_message("Hello")

    message2: str = "My name is Nathan"
    print_message(message2)

    c: int = add(3, 4)
    print("c =", c)

    nathan = Person("Nathan", 24)
    print(f"Name: {nathan.get_name()}, Age: {nathan.get_age()}")

if __name__ == "__main__":
    main()