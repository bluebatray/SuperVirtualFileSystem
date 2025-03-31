Implement a simple virtual filesystem (i.e. one existing only in your program, there is no interfacing with the real filesystem on disk) and a simple shell to interact with it.
The filesystem root directory can contain files and directories. Directories can contain multiple files and/or directories, etc.

Goal
This structure is believed to provide a comprehensive exercise in C++ OOP, demonstrating encapsulation, inheritance, polymorphism, and composition, while also tackling real-world scheduling concepts.

Acceptance Criteria
As a virtual filesystem app user:

I want to decide between backslash and forward slash used on the application startup
I expect README.md file containing some user manual section
I want to know where in the running filesystem app I currently am located
I need the following set of commands with typical behaviour expected:
cp X Y - copy a file or a directory from path X to path Y
mv X Y - move (or rename) a file or a directory from path X to path Y
cd X - change the current working directory (or .. to go up a level)
mkdir X - create a directorynamed X
rm X - remove a file named X or an empty directory named X
create X File Text - create a file named X with contents "File Text"
cat X - print contents of a file named X
ls - print files and directoriers in the current working directory
stat X - prints metadata of a directory / file
> stat Directory
Time of creation: 00:00:00 01-01-1970
Item count: 42

> stat File
Time of creation: 13:02:42 08-04-2024
Size: 42 bytes
Like in real, the dot represents current directory and it's possible to write longer paths like \dir\ or .\dir2\f.txt or ..\..\dir7\ and similar.
Nice to have
Tab ⭾ key for autocomplete where it makes sense would be great.
Definition of Done
Avoid mixing up any user interaction with the business logic.
Keep the business layer in stand-alone the DLL library project (so it can be sold separately).
Your code needs to follow some coding guidelines.
You can use some existing or even formatting tools, etc.
The code needs to meet language standard of C++11 at minimum, any constructs of newer standards are more than welcome.
