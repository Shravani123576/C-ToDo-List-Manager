# C Command-Line To-Do List Manager

A robust command-line interface (CLI) To-Do List application developed in C, showcasing proficiency in file handling, data structures, and user input validation for practical task management. It allows users to manage daily tasks, including adding, viewing, marking complete, and deleting tasks with data persistence.

## Features
* **Add Tasks:** Easily add new tasks with a description.
* **View Tasks:** Display all tasks with their unique IDs and completion status.
* **Mark Complete:** Mark tasks as completed using their ID.
* **Delete Tasks:** Remove tasks from the list by ID.
* **Persistent Storage:** All tasks are saved to `tasks.txt` and loaded automatically on startup, ensuring data is not lost across sessions.
* **User-Friendly CLI:** Clear prompts, formatted output, and color-coding (ANSI escape codes) for an enhanced user experience.

## Demo
A quick walkthrough of the To-Do List Manager in action:

![To-Do List Manager Demo](https://github.com/user-attachments/assets/69ca8fee-a70b-4a93-8059-45546fe22318)


## Screenshots
Visual examples of the application's interface:

### Main Menu
![Main Menu Screenshot](https://github.com/user-attachments/assets/6d120e21-54a6-4e56-8f43-8b4ace892f37)



### Viewing Tasks
![Viewing Tasks Screenshot](https://github.com/user-attachments/assets/4b863ce0-b7b6-43e9-8d75-1d1009b22d72)




## How to Compile and Run
This project requires a C compiler (like GCC).

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/Shravani123576/C-ToDo-List-Manager.git](https://github.com/Shravani123576/C-ToDo-List-Manager.git)
    cd C-ToDo-List-Manager
    ```
2.  **Compile the code:**
    ```bash
    gcc todo.c -o todo -Wall -Wextra -std=c99
    ```
3.  **Run the executable:**
    * **On Windows:**
        ```bash
        todo.exe
        ```
        (or just `todo`)
    * **On Linux/macOS:**
        ```bash
        ./todo
        ```

## Learning & Reflection
This project was instrumental in building my foundational understanding of C programming. It provided hands-on experience with:
* **File I/O:** Implementing persistent data storage for the first time.
* **Data Structures (`structs`):** Organizing complex data efficiently.
* **Modular Design:** Breaking down problems into manageable functions for better code organization.
* **Input Validation & Error Handling:** Learning to create robust and user-friendly applications by anticipating and managing invalid inputs or file issues.
* **Core Logic Building:** Understanding how instructions translate into functional software at a low level, which has been invaluable for developing my problem-solving skills.

This experience has been a cornerstone in my coding journey, building a strong base as I continue my studies in my 2nd year.

---
Developed by Shravani [Shravani Barhanpurkar]
Connect with me on LinkedIn: [www.linkedin.com/in/
shravani-barhanpurkar-1a78a0319
]
