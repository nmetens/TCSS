#####################
# Example 0:

"""
def add(a, b):
    return a + b

sum = add(5, 3)
print(sum)
"""

add = lambda a, b: print(a + b)

add(5, 1)

#####################
# Example 1:

def double(n):
    return 2 * n

x = lambda n: 2*n

print("double(7):", double(7))
print("x(7):", x(7))

######################
# Example 2:

nums = [3, 4, 1, 6, 9, 6]

"""
i = 0
while i < len(nums):
    print(f"num {i}: {nums[i]}")
    i += 1
"""

# Lambda:
print_values = lambda values: print(" ".join(str(x) for x in values))
print_values(nums)

######################
# Example 3:

# Challenge. Turn this code into a single lambda:
def process(nums):
    """
        Takes a list as input, loops through the list,
        checks if the current num is even, if so, add its
        value multiplied by itself to the new list.

        :param nums, a list of numbers, list
        :return sum, sum of all even values multiplied by themselves, list
    """
    result = []
    for n in nums:
        if n % 2 == 0:
            result.append(n * n)
    return sum(result)

summ = process(nums)
print(summ)

# Lambda:
total_even = lambda nums: print(f"sum of even squars: {sum(x*x for x in nums if x % 2 == 0)}")
total_even([2, 4])

######################
# Example 4:

def positives(nums):
    """
        Given a list of nums, return a list of only the positive ones.
    """
    result = []
    for n in nums:
        if n > 0:
            result.append(n)
    return result

vals = [-10, 3, -51, -1, 14, 10, -3]
print(positives(vals))

# Lambda equivalent:
positive = lambda nums: [x for x in nums if x> 0]
pos = positive(vals)
print(pos)

######################
# Example 5:

def double_strings(strings):
    """
        Return a list where each item in the strings list is doubled.
    """
    doubled = []
    for s in strings:
        doubled.append(s + s)
    return doubled

print(double_strings(['g', 'hi', 'aaa']))

# Double lambda:
d = lambda x: x + x
# print(d('a'))
double = lambda strings: print(list(map(d, strings)))
double(['x', 'nathan'])
