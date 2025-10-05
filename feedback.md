
**10/4/2025**
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* To provide you with thorough feedback, your instructor reads your code line by line, sometimes multiple times. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main()  and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise.
* Posted instructions are not optional, and not following the instructions will result in a lower grade. It applies to all assignments in this course.
* excessive use of printf/cout/cin/ file stream/stringstream and/or endl and/or << >>; applies to all output, not just menu-5
* if a user enters a value of the wrong data type, the program goes into an infinite loop; should create a highly reusable function that takes an error message string as a parameter, clears the failed input, and outputs the error message to be called in the default case of the menu switch -5
  * Should print a couple of blank lines before the menu to separate from the lines of text above it
  * no need for the “.” at the end of menu options; it is just clutter but no useful info to a user* no need for the “.” at the end of menu options; it is just clutter but no useful info to a user
  * input>>name>>id>gpal;
```text
//e.g.
cout << "\n\nMenu:\n”
“1. Encrypt\n”
“2. Decrypt\n”
“3. Quit\n"<<endl;
```


* missing toString() -5

*44 and like poor and redundant technique; all setter functions, including all c’tors’, should be calling setter function that sets all member variables (e.g., setAll()); it helps to avoid redundancy, promotes consistency, and ease of future modifications, call setAll() inside all other individual setter functions, including c’tor(s); this way validation and set statements are not all over the class code; you can make validator functions static so they can be called without an object; see assignment -5
* 73 and like multiple return statements in a non-recursive function; may result in unreachable return; use if/else, use a variable to store the results and return the variable; e.g. a function to check the length of a string, function to validate account number,  short validations can be done in the return statement; e.g.  return a<MIN_LENGTH;  e.g. return a\*6==b\*7;   -5
* 98 and like if it's not 1 or 0 make it a constant -5
* may not use regular expressions/lambda/iterators -5
*  94 and like modularization: each menu option should have its own function with a possible exception of the QUIT case; as a rule of thumb, if a case in a switch has more than 2 statements, make it a function;  all menus should be implemented using switch and enum; see assignment -2
* readability, comments; do not state the obvious, do not reiterate/duplicate the code, remove outdated code; comments are supposed to help and not create unnecessary clutter; comments should be to the right of the statement whenever possible, not above=> those who need to read them – will find them and read, those who do not will go to the next line; "Code never lies, comments sometimes do." - Ron Jeffries”; what is the purpose of the comments as this(ese) one(s)? -2

```text

// Global constants
const string INPUT_FILE = "accounts.txt";
// Function prototypes
bool isValidSSN(const string&);
```
* 22-24 – should have been member functions -2
* 35 and like: to promote strong exception guarantee, all variables, including members of struct and classes, should be initialized to appropriate default values at the time of definition/declaration;  const should be used to store default values; every var/obj should be defined on its own -2 
 * uses on or more of the following: non-allowed libraries, break (Ok in switch), return or exit() in loops and ifs, go to or continue, empty return (e.g., return;), infinite loops (while(true) or similar), void function with a return statement;  there is no situation where same effect cannot be achieved by a logical statement; in other words, there is no situation in this realm that cannot be described by using a combination of relational, comparison, and logical operators; you can always  write a loop condition to exit naturally when needed; see the syllabus –   stopped grading 
