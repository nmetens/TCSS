# Pointers and Dynamic Memory

## Pointer Basics

**Pointers hold the address of a variable in memory.** 

Simple, that's it, they refer to a variable's address.

Their values are an address.

Just like the values of an `int` are whole numbers and
the values of a `char` are single characters, the values
of pointers are addresses.

Pointers can "point" to a certain type of variable.

Remember the types: *int*, *char*, *bool*, *float*, *double*.

To create a pointer to an int, we do this notation:

`int * number_pointer;`

We tend to read this backwards as follows: "integer_pointer is
a pointer to an int."

However, at this very moment, it doesn't hold an address, because
it is uninitialized!

Let's initialize the pointer to point to the address of an integer:

`int number = 10;
 number_pointer = &number;`

Notice that we have the `&` before the number variable, that' 
because pointers must hold an address of their type. Since
number_pointer is a pointer to an int, it can hold the address
in memory of number.

Now, because number_pointer holds the address of the variable number 
in memory, we can access its value by **dereferencing** it. 

Dereferencing means "go" to the address that the pointer holds. We
dereference the reference we hold, then we BECOME that value.

So, to BECOME number, we do this:

`*number_pointer;   // "*" is the dereference operator!`

Well, in this instance, it is useless, we want to do something with 
the value at the address that number_pointer points to (references).

Let's change its value!

`*number_pointer += 1`

What happened to number? Well `*number_pointer` and `number` are the same
place in memory, therefore, if you change one, the other also changes.

Since `*number_pointer` is an alias to `number`, we incremented its value
by one. So now `number == 11`.




