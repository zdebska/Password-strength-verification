# Password-strength-verification
VUT: IZP_2021 Project1

# Description: 

The aim of the project is to create a program that receives a set of passwords on input and verifies for each of them whether the password meets all required rules. The passwords that pass the check will be output, the others will be discarded. 

### Security levels (controlled rules)

A total of 4 security levels are defined using 4 rules. The security level specifies that passwords must comply with all rules at the given and lower levels. 
Ie. eg security level 3 specifies that passwords must comply with rules 1, 2 and 3.

Some rules are parameterizable by an integer specified using the PARAM program argument. In the following list, this parameter is marked as X.

List of rules:

1. Password contains at least 1 uppercase and 1 lowercase letter.
2. The password contains characters from at least X groups (if the number X is greater than 4, this means all groups). The groups considered are:
  - lowercase letters (a-z)
  - capital letters (A-Z)
  - numbers (0-9)
  - special characters (at least non-alphanumeric characters from the ASCII table in positions 33-126 32-126 must be supported, ie including a space)
3. The password does not contain the same sequence of characters at least X.
4. The password does not contain two identical substrings of length at least X.

## Implementation details
### Input data (password list)
The list of passwords is passed to the program on standard input (stdin). Each password is entered on a separate line and contains only ASCII text data, except for the newline character. The maximum length of the password is 100 characters, otherwise it is invalid data. The program must support an unlimited number of passwords on entry.

### Program output
The stdout program prints passwords from the input list, each on a separate line, that meet the required security level specified as the LEVEL argument. Passwords must be listed without change and in the same order in which they appeared on the entry.

After the output list of passwords, the program then optionally (if the --stats argument is specified) displays statistics (various characters, minimum length, average length).

## Detailed specifications
Implement the program in the source file "pwcheck.c". Input data (password list) will be read from standard input (stdin), output (filtered password list) will be printed on standard output (stdout).

# Syntax to run the program
````
./pwcheck LEVEL PARAM [--stats] 
````
- (./pwcheck indicates the location and name of the program)

#### LEVEL
an integer in the interval [1, 4] that specifies the required security level (see below)
#### PARAM
positive integer that specifies an additional rule parameter (see below)
#### --stats
if specified, determines whether summary statistics of the analyzed passwords should be displayed at the end of the program

# Project results
### 9.3/10 points
