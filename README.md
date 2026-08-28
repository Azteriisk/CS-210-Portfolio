> **Course**: CS 210: Programming Languages  
> **Description**: Programming Languages & Algorithms (C++) Portfolio  
> **Part of**: [CS SWE Degree Path](https://github.com/Azteriisk/CS-SWE-Degree-Path)

---

# Corner Grocer – CS 210 Project  

## Project Description  
This project, **Corner Grocer**, was developed in C++ as part of CS 210. The program reads grocery purchase data from an input file, counts the frequency of each item, and provides a menu for interacting with that data. Users can:  

1. Look up the frequency of a single item  
2. Print the full list of items with counts  
3. Print a histogram showing counts visually  
4. Exit the program  

The program also writes results to a backup file (`frequency.dat`) to ensure data persistence.  

---

## Build and Run Instructions  
1. Make sure `CS210_Project_Three_Input_File.txt` is in the same directory as the source files.  
2. Compile the program:  
   ```bash
   g++ main.cpp -o CornerGrocer
   ```  
3. Run the executable:  
   ```bash
   ./CornerGrocer
   ```  
4. The program will generate `frequency.dat` in the same directory.  

> ⚠️ If you load a different input file, place it in the same directory and name it appropriately.  

## Portfolio Reflection  

**Project Summary**  
For this project, I developed the Corner Grocer program in C++. The program reads grocery purchases from an input file, counts the frequency of each item, and allows the user to interact with that data through a menu. Users can look up the frequency of a single item, view all items with counts, generate a histogram, or exit the program. The data is also saved into a backup file (`frequency.dat`) so there is always a record available.  

**Strengths in My Work**  
I structured the program around a single class, `GroceryTracker`, which keeps the code organized and leaves `main()` short and easy to follow. Using `std::map<std::string, int>` was a good design choice because it automatically sorts the items alphabetically, making the results cleaner to read. I also added quality-of-life features such as case-insensitive lookups and input validation to prevent crashes.  

**Areas for Improvement**  
If I were to enhance the program further, I would expand input validation, for example by handling corrupted files or giving users clearer error messages. I would also consider separating the backup functionality into its own class, which would make the code even more modular and adaptable. These improvements would help make the code more robust, secure, and easier to maintain.  

**Challenges and How I Overcame Them**  
The most challenging part was building the histogram output in a way that was both simple and user-friendly. I overcame this by iterating on small test cases, printing output step by step until I was confident the formatting worked. Careful testing against different data sets helped ensure the output was accurate.  

**Transferable Skills**  
This project strengthened my ability to use C++ data structures like maps effectively. It also improved my skills in organizing code with classes, handling file I/O, and designing user-friendly menus. These skills are transferable to many other programming contexts, whether in C++ or other languages that share similar concepts.  

**Maintaining Readability and Adaptability**  
I made the program maintainable by using clear function names, consistent indentation, and meaningful variable names. The class design keeps functionality modular, so new features (such as additional menu options or alternate output formats) could be added without rewriting the program’s core logic. This makes the project both readable for others and adaptable for future work.  

---

## Repository Structure  
```
CornerGrocer/
│── main.cpp
│── CS210_Project_Three_Input_File.txt
│── frequency.dat
│── README.md
```

