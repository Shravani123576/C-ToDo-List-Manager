#include <stdio.h>    // Standard input/output functions (printf, scanf, fopen, fclose, etc.)
#include <stdlib.h>   // Standard library functions (malloc, free, exit, system)
#include <string.h>   // String manipulation functions (strcpy, strcmp, strlen, strcspn)
#include <stdbool.h>  // Boolean type (true, false)

// Define ANSI escape codes for text colors (for making output attractive)
// These codes might not work on all terminals (e.g., older Windows Command Prompt).
// Modern terminals (Linux, macOS, Git Bash on Windows, Windows Terminal) support them.
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Maximum length for a task description
#define MAX_TASK_LEN 256
// Maximum number of tasks the list can hold
#define MAX_TASKS 100
// Name of the file where tasks will be saved
#define FILENAME "tasks.txt"

// Structure to represent a single To-Do task
typedef struct {
    int id;                 // Unique identifier for the task
    char description[MAX_TASK_LEN]; // Description of the task
    bool completed;         // Status: true if completed, false otherwise
} Task;

// Global array to store tasks (simple for this mini-project, dynamic array/linked list
// would be more advanced but adds complexity)
Task tasks[MAX_TASKS];
// Current number of tasks in the array
int taskCount = 0;

// --- Function Prototypes ---
void displayMenu();
void addTask();
void viewTasks();
void markTaskComplete();
void deleteTask();
void saveTasks();
void loadTasks();
void clearInputBuffer(); // Helper function to clear stdin buffer

// --- Main Function ---
int main() {
    // Clear the console screen (system-dependent)
    // For Windows: "cls", For Linux/macOS: "clear"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf(BOLD BLUE "Welcome to the C To-Do List Manager!\n" RESET);

    // Load tasks from file at the start of the program
    loadTasks();

    int choice;
    do {
        displayMenu(); // Show the main menu
        printf(BOLD CYAN "Enter your choice: " RESET);
        // Read user's choice
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input. Please enter a number.\n" RESET);
            clearInputBuffer(); // Clear buffer to prevent infinite loop
            choice = -1; // Set to an invalid choice to re-display menu
            continue;
        }
        clearInputBuffer(); // Clear remaining newline character from buffer

        // Process user's choice using a switch statement
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                markTaskComplete();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf(YELLOW "Exiting program. Saving tasks...\n" RESET);
                saveTasks(); // Save tasks before exiting
                printf(GREEN "Tasks saved successfully. Goodbye!\n" RESET);
                break;
            default:
                printf(RED "Invalid choice. Please try again.\n" RESET);
                break;
        }
        printf("\n"); // Add a newline for better readability between operations
    } while (choice != 5); // Loop until user chooses to exit

    return 0; // Indicate successful program execution
}

// --- Function Implementations ---

/**
 * @brief Displays the main menu options to the user.
 */
void displayMenu() {
    printf(BOLD MAGENTA "--- To-Do List Menu ---\n" RESET);
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark Task as Complete\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n");
    printf(BOLD MAGENTA "-----------------------\n" RESET);
}

/**
 * @brief Adds a new task to the list.
 * Prompts the user for a task description and assigns a unique ID.
 */
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf(RED "Task list is full. Cannot add more tasks.\n" RESET);
        return;
    }

    printf(CYAN "Enter task description: " RESET);
    // Read the task description, including spaces
    // fgets reads up to MAX_TASK_LEN-1 characters or until a newline
    if (fgets(tasks[taskCount].description, MAX_TASK_LEN, stdin) == NULL) {
        printf(RED "Error reading task description.\n" RESET);
        return;
    }
    // Remove the trailing newline character that fgets might include
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = '\0';

    // Basic validation for empty description
    if (strlen(tasks[taskCount].description) == 0) {
        printf(RED "Task description cannot be empty. Task not added.\n" RESET);
        return;
    }

    // Assign a unique ID (simple increment for now)
    // If tasks are loaded, the ID will continue from the last loaded task's ID + 1
    tasks[taskCount].id = (taskCount > 0) ? (tasks[taskCount - 1].id + 1) : 1;
    tasks[taskCount].completed = false; // New tasks are always incomplete

    taskCount++; // Increment the total task count
    printf(GREEN "Task added successfully! (ID: %d)\n" RESET, tasks[taskCount - 1].id);
}

/**
 * @brief Displays all tasks currently in the list.
 * Shows ID, status (completed/incomplete), and description.
 */
void viewTasks() {
    if (taskCount == 0) {
        printf(YELLOW "No tasks to display. Add some tasks first!\n" RESET);
        return;
    }

    printf(BOLD BLUE "--- Your To-Do Tasks ---\n" RESET);
    printf(BOLD "%-5s %-10s %s\n" RESET, "ID", "Status", "Description");
    printf("----------------------------------------\n");

    for (int i = 0; i < taskCount; i++) {
        // Print status: [X] for completed, [ ] for incomplete
        const char* status = tasks[i].completed ? GREEN "[X]" RESET : RED "[ ]" RESET;
        // Print description with color based on completion status
        const char* descriptionColor = tasks[i].completed ? GREEN : RESET; // Only green if completed
        printf("%-5d %s %s%s%s\n", tasks[i].id, status, descriptionColor, tasks[i].description, RESET);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Marks a task as complete based on its ID.
 * Prompts the user for the task ID.
 */
void markTaskComplete() {
    if (taskCount == 0) {
        printf(YELLOW "No tasks to mark complete. Add tasks first!\n" RESET);
        return;
    }

    int taskId;
    printf(CYAN "Enter the ID of the task to mark as complete: " RESET);
    if (scanf("%d", &taskId) != 1) {
        printf(RED "Invalid input. Please enter a number.\n" RESET);
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == taskId) {
            tasks[i].completed = true; // Set task as completed
            printf(GREEN "Task ID %d marked as complete.\n" RESET, taskId);
            found = true;
            break;
        }
    }

    if (!found) {
        printf(RED "Task with ID %d not found.\n" RESET, taskId);
    }
}

/**
 * @brief Deletes a task from the list based on its ID.
 * Prompts the user for the task ID.
 */
void deleteTask() {
    if (taskCount == 0) {
        printf(YELLOW "No tasks to delete.\n" RESET);
        return;
    }

    int taskId;
    printf(CYAN "Enter the ID of the task to delete: " RESET);
    if (scanf("%d", &taskId) != 1) {
        printf(RED "Invalid input. Please enter a number.\n" RESET);
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int foundIndex = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == taskId) {
            foundIndex = i; // Store the index of the task to be deleted
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift elements after the deleted task to the left
        for (int i = foundIndex; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--; // Decrement the total task count
        printf(GREEN "Task ID %d deleted successfully.\n" RESET, taskId);
    } else {
        printf(RED "Task with ID %d not found.\n" RESET, taskId);
    }
}

/**
 * @brief Saves all current tasks to a text file (FILENAME).
 * Each task is saved on a new line with its ID, completion status, and description.
 */
void saveTasks() {
    FILE *file = fopen(FILENAME, "w"); // Open file in write mode ("w" overwrites existing content)
    if (file == NULL) {
        printf(RED "Error: Could not open file for writing tasks.\n" RESET);
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        // Format: ID,CompletedStatus,Description
        // Example: 1,0,Buy groceries
        // Example: 2,1,Finish C project
        fprintf(file, "%d,%d,%s\n", tasks[i].id, tasks[i].completed ? 1 : 0, tasks[i].description);
    }

    fclose(file); // Close the file
}

/**
 * @brief Loads tasks from the text file (FILENAME) into the task list.
 * Reads each line and parses the task details.
 */
void loadTasks() {
    FILE *file = fopen(FILENAME, "r"); // Open file in read mode
    if (file == NULL) {
        printf(YELLOW "No existing tasks file found. Starting with an empty list.\n" RESET);
        return; // File doesn't exist, start with empty list
    }

    taskCount = 0; // Reset task count before loading
    char line[MAX_TASK_LEN + 10]; // Buffer to read each line (+10 for ID/status/commas)
    int maxId = 0; // To ensure new tasks get unique IDs after loading

    // Read lines until end of file or max tasks reached
    while (fgets(line, sizeof(line), file) != NULL && taskCount < MAX_TASKS) {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Parse the line: ID,CompletedStatus,Description
        // Using sscanf with a format string to extract values
        int id, completedStatus;
        char description[MAX_TASK_LEN];

        // sscanf returns the number of items successfully matched and assigned.
        // We expect 3 items: id, completedStatus, description.
        if (sscanf(line, "%d,%d,%[^\n]", &id, &completedStatus, description) == 3) {
            tasks[taskCount].id = id;
            tasks[taskCount].completed = (bool)completedStatus;
            strcpy(tasks[taskCount].description, description);
            
            // Update maxId to ensure new tasks get higher IDs
            if (id > maxId) {
                maxId = id;
            }
            taskCount++;
        } else {
            printf(RED "Warning: Skipping malformed line in tasks file: %s\n" RESET, line);
        }
    }
    
    // If tasks were loaded, ensure the next new task gets an ID greater than any loaded task.
    // This is a simple way to handle ID assignment after loading.
    // A more robust solution for ID management might involve a separate counter or searching for the max ID.
    if (taskCount > 0) {
        // Find the maximum ID among loaded tasks and set the next ID appropriately
        int currentMaxId = 0;
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].id > currentMaxId) {
                currentMaxId = tasks[i].id;
            }
        }
        // When adding a new task, its ID will be currentMaxId + 1.
        // For simplicity in this code, new tasks get ID `tasks[taskCount-1].id + 1` which works
        // if tasks are always added sequentially. A better approach for loaded IDs would be:
        // tasks[taskCount].id = currentMaxId + 1; when adding.
        // For this project, the current ID assignment in addTask() is sufficient if IDs are always increasing.
    }


    printf(GREEN "Loaded %d tasks from %s.\n" RESET, taskCount, FILENAME);
    fclose(file); // Close the file
}

/**
 * @brief Clears the input buffer (stdin) after reading user input.
 * Prevents issues with leftover newline characters affecting subsequent `fgets` calls.
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
