# c_72_scanf

## DESCRIPTION

Write a safer function then `scanf` to get integer number from user, check as much edge cases as possible.

There is no input error checking in `scanf` function. If the type of the input we want to read is integer but the user inputs a string, we get 0 value which is not correct. Instead of this behaviour the scanf function should ignore the input and ask the user for another input.
This can be implemented into our new `get_int` function.

Nearly all edge cases solved within the get_int function, see the unsolved edge cases below:

- the input number is too big -> it will cause an integer overflow
- the function returns 0 in case of failure
