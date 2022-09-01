print('Hi')
array = []
array.append(1)
array.append(2)
print(array)

# examples hmm
# f is needed for input; something like `${}` for ts but in python 
my_input = [1, 2, 3, 4, 5]
 
print(f'Current Numbers List {my_input}')
 
number = int(input("Please enter a number to be added:\n"))
 
index = int(input(f'Enter the index between 0 and {len(my_input) - 1} to add the given number:\n'))
 
my_input.insert(index, number)
 
print(f'Updated List {my_input}')

## write python3 in the command line instead of python
# ie 'python3 hello.py'