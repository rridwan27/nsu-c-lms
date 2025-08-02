#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_COURSENAME 100
#define MAX_CONTENT 1000
#define MAX_USERS 100
#define MAX_COURSES 50
#define MAX_ENROLLMENTS 200
#define MAX_MARKS 200
#define MAX_ATTENDANCE 500

// User roles
typedef enum {
    ADMIN = 1,
    TEACHER = 2,
    STUDENT = 3
} Role;

// Structure definitions
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    Role role;
} User;

typedef struct {
    int course_id;
    char course_name[MAX_COURSENAME];
    char teacher_username[MAX_USERNAME];
} Course;

typedef struct {
    int course_id;
    char student_username[MAX_USERNAME];
} Enrollment;

typedef struct {
    int course_id;
    char student_username[MAX_USERNAME];
    float marks;
} Mark;

typedef struct {
    int course_id;
    char student_username[MAX_USERNAME];
    char date[12]; // Format: DD-MM-YYYY
    char status[10]; // "Present", "Absent", "Late"
} Attendance;

// Global variables
User users[MAX_USERS];
Course courses[MAX_COURSES];
Enrollment enrollments[MAX_ENROLLMENTS];
Mark marks[MAX_MARKS];
Attendance attendance[MAX_ATTENDANCE];

int user_count = 0;
int course_count = 0;
int enrollment_count = 0;
int mark_count = 0;
int attendance_count = 0;

char current_user[MAX_USERNAME];
Role current_role;

// Function prototypes
void load_data();
void save_data();
int login();
void register_user();
void admin_menu();
void teacher_menu();
void student_menu();
void create_course();
void assign_course();
void upload_materials();
void view_courses();
void view_materials();
void assign_marks();
void view_marks();
void take_attendance();
void view_attendance();
void add_user();
void change_user_role();
void clear_screen();
void pause_screen();
int find_user(const char* username);
int find_course(int course_id);
char* role_to_string(Role role);
Role string_to_role(const char* role_str);

// Utility functions
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_screen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

char* role_to_string(Role role) {
    switch(role) {
        case ADMIN: return "Admin";
        case TEACHER: return "Teacher";
        case STUDENT: return "Student";
        default: return "Unknown";
    }
}

Role string_to_role(const char* role_str) {
    if (strcmp(role_str, "Admin") == 0) return ADMIN;
    if (strcmp(role_str, "Teacher") == 0) return TEACHER;
    if (strcmp(role_str, "Student") == 0) return STUDENT;
    return STUDENT; // Default
}

int find_user(const char* username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

int find_course(int course_id) {
    for (int i = 0; i < course_count; i++) {
        if (courses[i].course_id == course_id) {
            return i;
        }
    }
    return -1;
}

// Data persistence functions
void load_data() {
    FILE *file;
    
    // Load users
    file = fopen("users.txt", "r");
    if (file) {
        char role_str[20];
        while (fscanf(file, "%s %s %s", users[user_count].username, 
                     users[user_count].password, role_str) == 3) {
            users[user_count].role = string_to_role(role_str);
            user_count++;
            if (user_count >= MAX_USERS) break;
        }
        fclose(file);
    }
    
    // Create default admin if no users exist
    if (user_count == 0) {
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        users[0].role = ADMIN;
        user_count = 1;
    }
    
    // Load courses
    file = fopen("courses.txt", "r");
    if (file) {
        while (fscanf(file, "%d %s %s", &courses[course_count].course_id,
                     courses[course_count].course_name,
                     courses[course_count].teacher_username) == 3) {
            course_count++;
            if (course_count >= MAX_COURSES) break;
        }
        fclose(file);
    }
    
    // Load enrollments
    file = fopen("enrollments.txt", "r");
    if (file) {
        while (fscanf(file, "%d %s", &enrollments[enrollment_count].course_id,
                     enrollments[enrollment_count].student_username) == 2) {
            enrollment_count++;
            if (enrollment_count >= MAX_ENROLLMENTS) break;
        }
        fclose(file);
    }
    
    // Load marks
    file = fopen("marks.txt", "r");
    if (file) {
        while (fscanf(file, "%d %s %f", &marks[mark_count].course_id,
                     marks[mark_count].student_username,
                     &marks[mark_count].marks) == 3) {
            mark_count++;
            if (mark_count >= MAX_MARKS) break;
        }
        fclose(file);
    }
    
    // Load attendance
    file = fopen("attendance.txt", "r");
    if (file) {
        while (fscanf(file, "%d %s %s %s", &attendance[attendance_count].course_id,
                     attendance[attendance_count].student_username,
                     attendance[attendance_count].date,
                     attendance[attendance_count].status) == 4) {
            attendance_count++;
            if (attendance_count >= MAX_ATTENDANCE) break;
        }
        fclose(file);
    }
}

void save_data() {
    FILE *file;
    
    // Save users
    file = fopen("users.txt", "w");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%s %s %s\n", users[i].username, users[i].password,
                   role_to_string(users[i].role));
        }
        fclose(file);
    }
    
    // Save courses
    file = fopen("courses.txt", "w");
    if (file) {
        for (int i = 0; i < course_count; i++) {
            fprintf(file, "%d %s %s\n", courses[i].course_id,
                   courses[i].course_name, courses[i].teacher_username);
        }
        fclose(file);
    }
    
    // Save enrollments
    file = fopen("enrollments.txt", "w");
    if (file) {
        for (int i = 0; i < enrollment_count; i++) {
            fprintf(file, "%d %s\n", enrollments[i].course_id,
                   enrollments[i].student_username);
        }
        fclose(file);
    }
    
    // Save marks
    file = fopen("marks.txt", "w");
    if (file) {
        for (int i = 0; i < mark_count; i++) {
            fprintf(file, "%d %s %.2f\n", marks[i].course_id,
                   marks[i].student_username, marks[i].marks);
        }
        fclose(file);
    }
    
    // Save attendance
    file = fopen("attendance.txt", "w");
    if (file) {
        for (int i = 0; i < attendance_count; i++) {
            fprintf(file, "%d %s %s %s\n", attendance[i].course_id,
                   attendance[i].student_username, attendance[i].date,
                   attendance[i].status);
        }
        fclose(file);
    }
}

// Authentication functions
int login() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    printf("=== LOGIN ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    int user_index = find_user(username);
    if (user_index != -1 && strcmp(users[user_index].password, password) == 0) {
        strcpy(current_user, username);
        current_role = users[user_index].role;
        printf("Login successful! Welcome, %s (%s)\n", 
               username, role_to_string(current_role));
        pause_screen();
        return 1;
    } else {
        printf("Invalid username or password!\n");
        pause_screen();
        return 0;
    }
}

void register_user() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    if (user_count >= MAX_USERS) {
        printf("Maximum users reached!\n");
        pause_screen();
        return;
    }
    
    printf("=== REGISTER ===\n");
    printf("Username: ");
    scanf("%s", username);
    
    if (find_user(username) != -1) {
        printf("Username already exists!\n");
        pause_screen();
        return;
    }
    
    printf("Password: ");
    scanf("%s", password);
    
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].role = STUDENT; // Default role
    user_count++;
    
    save_data();
    printf("Registration successful! Default role: Student\n");
    pause_screen();
}

// Attendance functions
void take_attendance() {
    int course_id;
    char date[12];
    time_t now = time(0);
    struct tm *local = localtime(&now);
    
    printf("=== TAKE ATTENDANCE ===\n");
    printf("Course ID: ");
    scanf("%d", &course_id);
    
    int course_index = find_course(course_id);
    if (course_index == -1 || 
        strcmp(courses[course_index].teacher_username, current_user) != 0) {
        printf("You are not assigned to this course!\n");
        pause_screen();
        return;
    }
    
    // Default to today's date, but allow teacher to change
    sprintf(date, "%02d-%02d-%04d", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
    printf("Date (DD-MM-YYYY) [%s]: ", date);
    char input_date[12];
    scanf("%s", input_date);
    if (strlen(input_date) > 1) {
        strcpy(date, input_date);
    }
    
    printf("\nStudents enrolled in %s:\n", courses[course_index].course_name);
    printf("=====================================\n");
    
    // Show all enrolled students and take attendance
    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].course_id == course_id) {
            char status[10];
            int choice;
            
            printf("Student: %s\n", enrollments[i].student_username);
            printf("1. Present  2. Absent  3. Late\n");
            printf("Choice: ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1: strcpy(status, "Present"); break;
                case 2: strcpy(status, "Absent"); break;
                case 3: strcpy(status, "Late"); break;
                default: strcpy(status, "Absent"); break;
            }
            
            // Check if attendance already exists for this student on this date
            int found = 0;
            for (int j = 0; j < attendance_count; j++) {
                if (attendance[j].course_id == course_id &&
                    strcmp(attendance[j].student_username, enrollments[i].student_username) == 0 &&
                    strcmp(attendance[j].date, date) == 0) {
                    strcpy(attendance[j].status, status);
                    found = 1;
                    break;
                }
            }
            
            // If not found and we have space, add new attendance record
            if (!found && attendance_count < MAX_ATTENDANCE) {
                attendance[attendance_count].course_id = course_id;
                strcpy(attendance[attendance_count].student_username, enrollments[i].student_username);
                strcpy(attendance[attendance_count].date, date);
                strcpy(attendance[attendance_count].status, status);
                attendance_count++;
            }
            
            printf("Marked as %s\n\n", status);
        }
    }
    
    save_data();
    printf("Attendance saved successfully!\n");
    pause_screen();
}

void view_attendance() {
    printf("=== ATTENDANCE RECORDS ===\n");
    
    if (current_role == ADMIN) {
        printf("All Attendance Records:\n");
        printf("Course | Student | Date | Status\n");
        printf("--------------------------------\n");
        for (int i = 0; i < attendance_count; i++) {
            int course_index = find_course(attendance[i].course_id);
            printf("%-6s | %-7s | %-10s | %s\n",
                   course_index != -1 ? courses[course_index].course_name : "Unknown",
                   attendance[i].student_username,
                   attendance[i].date,
                   attendance[i].status);
        }
    } else if (current_role == TEACHER) {
        int course_id;
        printf("Enter Course ID to view attendance (0 for all my courses): ");
        scanf("%d", &course_id);
        
        printf("\nAttendance for My Courses:\n");
        printf("Course | Student | Date | Status\n");
        printf("--------------------------------\n");
        
        for (int i = 0; i < attendance_count; i++) {
            int course_index = find_course(attendance[i].course_id);
            if (course_index != -1 &&
                strcmp(courses[course_index].teacher_username, current_user) == 0 &&
                (course_id == 0 || attendance[i].course_id == course_id)) {
                printf("%-6s | %-7s | %-10s | %s\n",
                       courses[course_index].course_name,
                       attendance[i].student_username,
                       attendance[i].date,
                       attendance[i].status);
            }
        }
    } else if (current_role == STUDENT) {
        printf("My Attendance Records:\n");
        printf("Course | Date | Status\n");
        printf("----------------------\n");
        
        int total_classes = 0, present_classes = 0;
        
        for (int i = 0; i < attendance_count; i++) {
            if (strcmp(attendance[i].student_username, current_user) == 0) {
                int course_index = find_course(attendance[i].course_id);
                printf("%-6s | %-10s | %s\n",
                       course_index != -1 ? courses[course_index].course_name : "Unknown",
                       attendance[i].date,
                       attendance[i].status);
                
                total_classes++;
                if (strcmp(attendance[i].status, "Present") == 0 || 
                    strcmp(attendance[i].status, "Late") == 0) {
                    present_classes++;
                }
            }
        }
        
        if (total_classes > 0) {
            float attendance_percentage = (float)present_classes / total_classes * 100;
            printf("\nAttendance Summary:\n");
            printf("Total Classes: %d\n", total_classes);
            printf("Classes Attended: %d\n", present_classes);
            printf("Attendance Percentage: %.2f%%\n", attendance_percentage);
        }
    }

// Admin functions
void admin_menu() {
    int choice;
    
    while (1) {
        clear_screen();
        printf("=== ADMIN MENU ===\n");
        printf("Welcome, %s\n\n", current_user);
        printf("1. Create Course\n");
        printf("2. Add User\n");
        printf("3. Change User Role\n");
        printf("4. Assign Course to Teacher\n");
        printf("5. Assign Course to Student\n");
        printf("6. View All Courses\n");
        printf("7. View Course Materials\n");
        printf("8. View All Marks\n");
        printf("9. View All Attendance\n");
        printf("10. Logout\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: create_course(); break;
            case 2: add_user(); break;
            case 3: change_user_role(); break;
            case 4: assign_course(); break;
            case 5: assign_course(); break;
            case 6: view_courses(); break;
            case 7: view_materials(); break;
            case 8: view_marks(); break;
            case 9: view_attendance(); break;
            case 10: return;
            default: printf("Invalid choice!\n"); pause_screen(); break;
        }
    }
}

void create_course() {
    if (course_count >= MAX_COURSES) {
        printf("Maximum courses reached!\n");
        pause_screen();
        return;
    }
    
    printf("=== CREATE COURSE ===\n");
    printf("Course ID: ");
    scanf("%d", &courses[course_count].course_id);
    
    if (find_course(courses[course_count].course_id) != -1) {
        printf("Course ID already exists!\n");
        pause_screen();
        return;
    }
    
    printf("Course Name: ");
    scanf("%s", courses[course_count].course_name);
    
    strcpy(courses[course_count].teacher_username, "");
    course_count++;
    
    save_data();
    printf("Course created successfully!\n");
    pause_screen();
}

void add_user() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    int role_choice;
    
    if (user_count >= MAX_USERS) {
        printf("Maximum users reached!\n");
        pause_screen();
        return;
    }
    
    printf("=== ADD USER ===\n");
    printf("Username: ");
    scanf("%s", username);
    
    if (find_user(username) != -1) {
        printf("Username already exists!\n");
        pause_screen();
        return;
    }
    
    printf("Password: ");
    scanf("%s", password);
    printf("Role (1-Admin, 2-Teacher, 3-Student): ");
    scanf("%d", &role_choice);
    
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].role = (Role)role_choice;
    user_count++;
    
    save_data();
    printf("User added successfully!\n");
    pause_screen();
}

void change_user_role() {
    char username[MAX_USERNAME];
    int role_choice;
    
    printf("=== CHANGE USER ROLE ===\n");
    printf("Username: ");
    scanf("%s", username);
    
    int user_index = find_user(username);
    if (user_index == -1) {
        printf("User not found!\n");
        pause_screen();
        return;
    }
    
    printf("Current role: %s\n", role_to_string(users[user_index].role));
    printf("New role (1-Admin, 2-Teacher, 3-Student): ");
    scanf("%d", &role_choice);
    
    users[user_index].role = (Role)role_choice;
    save_data();
    printf("Role changed successfully!\n");
    pause_screen();
}

void assign_course() {
    int course_id;
    char username[MAX_USERNAME];
    
    printf("=== ASSIGN COURSE ===\n");
    printf("Course ID: ");
    scanf("%d", &course_id);
    
    int course_index = find_course(course_id);
    if (course_index == -1) {
        printf("Course not found!\n");
        pause_screen();
        return;
    }
    
    printf("Username: ");
    scanf("%s", username);
    
    int user_index = find_user(username);
    if (user_index == -1) {
        printf("User not found!\n");
        pause_screen();
        return;
    }
    
    if (users[user_index].role == TEACHER) {
        strcpy(courses[course_index].teacher_username, username);
        printf("Course assigned to teacher successfully!\n");
    } else if (users[user_index].role == STUDENT) {
        if (enrollment_count >= MAX_ENROLLMENTS) {
            printf("Maximum enrollments reached!\n");
            pause_screen();
            return;
        }
        enrollments[enrollment_count].course_id = course_id;
        strcpy(enrollments[enrollment_count].student_username, username);
        enrollment_count++;
        printf("Course assigned to student successfully!\n");
    } else {
        printf("Can only assign courses to teachers or students!\n");
    }
    
    save_data();
    pause_screen();
}

// Teacher functions
void teacher_menu() {
    int choice;
    
    while (1) {
        clear_screen();
        printf("=== TEACHER MENU ===\n");
        printf("Welcome, %s\n\n", current_user);
        printf("1. View My Courses\n");
        printf("2. Upload Course Materials\n");
        printf("3. View Course Materials\n");
        printf("4. Assign Marks\n");
        printf("5. View Student Marks\n");
        printf("6. Take Attendance\n");
        printf("7. View Attendance\n");
        printf("8. Logout\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: view_courses(); break;
            case 2: upload_materials(); break;
            case 3: view_materials(); break;
            case 4: assign_marks(); break;
            case 5: view_marks(); break;
            case 6: take_attendance(); break;
            case 7: view_attendance(); break;
            case 8: return;
            default: printf("Invalid choice!\n"); pause_screen(); break;
        }
    }
}

void upload_materials() {
    int course_id;
    char content[MAX_CONTENT];
    char filename[100];
    
    printf("=== UPLOAD MATERIALS ===\n");
    printf("Course ID: ");
    scanf("%d", &course_id);
    
    int course_index = find_course(course_id);
    if (course_index == -1) {
        printf("Course not found!\n");
        pause_screen();
        return;
    }
    
    if (strcmp(courses[course_index].teacher_username, current_user) != 0) {
        printf("You are not assigned to this course!\n");
        pause_screen();
        return;
    }
    
    printf("Enter content: ");
    getchar(); // Clear buffer
    fgets(content, MAX_CONTENT, stdin);
    
    sprintf(filename, "materials_%d.txt", course_id);
    FILE *file = fopen(filename, "a");
    if (file) {
        time_t now = time(0);
        fprintf(file, "\n--- Added on %s", ctime(&now));
        fprintf(file, "%s\n", content);
        fclose(file);
        printf("Materials uploaded successfully!\n");
    } else {
        printf("Error uploading materials!\n");
    }
    
    pause_screen();
}

void assign_marks() {
    int course_id;
    char student_username[MAX_USERNAME];
    float mark_value;
    
    printf("=== ASSIGN MARKS ===\n");
    printf("Course ID: ");
    scanf("%d", &course_id);
    
    int course_index = find_course(course_id);
    if (course_index == -1 || 
        strcmp(courses[course_index].teacher_username, current_user) != 0) {
        printf("You are not assigned to this course!\n");
        pause_screen();
        return;
    }
    
    printf("Student Username: ");
    scanf("%s", student_username);
    printf("Marks: ");
    scanf("%f", &mark_value);
    
    // Check if student is enrolled
    int enrolled = 0;
    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].course_id == course_id &&
            strcmp(enrollments[i].student_username, student_username) == 0) {
            enrolled = 1;
            break;
        }
    }
    
    if (!enrolled) {
        printf("Student is not enrolled in this course!\n");
        pause_screen();
        return;
    }
    
    // Update existing mark or add new one
    int mark_found = 0;
    for (int i = 0; i < mark_count; i++) {
        if (marks[i].course_id == course_id &&
            strcmp(marks[i].student_username, student_username) == 0) {
            marks[i].marks = mark_value;
            mark_found = 1;
            break;
        }
    }
    
    if (!mark_found && mark_count < MAX_MARKS) {
        marks[mark_count].course_id = course_id;
        strcpy(marks[mark_count].student_username, student_username);
        marks[mark_count].marks = mark_value;
        mark_count++;
    }
    
    save_data();
    printf("Marks assigned successfully!\n");
    pause_screen();
}

// Student functions
void student_menu() {
    int choice;
    
    while (1) {
        clear_screen();
        printf("=== STUDENT MENU ===\n");
        printf("Welcome, %s\n\n", current_user);
        printf("1. View My Courses\n");
        printf("2. View Course Materials\n");
        printf("3. View My Marks\n");
        printf("4. View My Attendance\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: view_courses(); break;
            case 2: view_materials(); break;
            case 3: view_marks(); break;
            case 4: view_attendance(); break;
            case 5: return;
            default: printf("Invalid choice!\n"); pause_screen(); break;
        }
    }
}

// Common functions
void view_courses() {
    printf("=== COURSES ===\n");
    
    if (current_role == ADMIN) {
        printf("All Courses:\n");
        for (int i = 0; i < course_count; i++) {
            printf("ID: %d, Name: %s, Teacher: %s\n",
                   courses[i].course_id, courses[i].course_name,
                   strlen(courses[i].teacher_username) > 0 ? 
                   courses[i].teacher_username : "Not Assigned");
        }
    } else if (current_role == TEACHER) {
        printf("My Assigned Courses:\n");
        for (int i = 0; i < course_count; i++) {
            if (strcmp(courses[i].teacher_username, current_user) == 0) {
                printf("ID: %d, Name: %s\n",
                       courses[i].course_id, courses[i].course_name);
            }
        }
    } else if (current_role == STUDENT) {
        printf("My Enrolled Courses:\n");
        for (int i = 0; i < enrollment_count; i++) {
            if (strcmp(enrollments[i].student_username, current_user) == 0) {
                int course_index = find_course(enrollments[i].course_id);
                if (course_index != -1) {
                    printf("ID: %d, Name: %s, Teacher: %s\n",
                           courses[course_index].course_id,
                           courses[course_index].course_name,
                           courses[course_index].teacher_username);
                }
            }
        }
    }
    
    pause_screen();
}

void view_materials() {
    int course_id;
    char filename[100];
    
    printf("=== VIEW MATERIALS ===\n");
    printf("Course ID: ");
    scanf("%d", &course_id);
    
    int course_index = find_course(course_id);
    if (course_index == -1) {
        printf("Course not found!\n");
        pause_screen();
        return;
    }
    
    // Check access permissions
    int has_access = 0;
    if (current_role == ADMIN) {
        has_access = 1;
    } else if (current_role == TEACHER &&
               strcmp(courses[course_index].teacher_username, current_user) == 0) {
        has_access = 1;
    } else if (current_role == STUDENT) {
        for (int i = 0; i < enrollment_count; i++) {
            if (enrollments[i].course_id == course_id &&
                strcmp(enrollments[i].student_username, current_user) == 0) {
                has_access = 1;
                break;
            }
        }
    }
    
    if (!has_access) {
        printf("You don't have access to this course!\n");
        pause_screen();
        return;
    }
    
    sprintf(filename, "materials_%d.txt", course_id);
    FILE *file = fopen(filename, "r");
    if (file) {
        char line[MAX_CONTENT];
        printf("\nCourse Materials for %s:\n", courses[course_index].course_name);
        printf("=====================================\n");
        while (fgets(line, MAX_CONTENT, file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("No materials available for this course.\n");
    }
    
    pause_screen();
}

void view_marks() {
    printf("=== MARKS ===\n");
    
    if (current_role == ADMIN) {
        printf("All Student Marks:\n");
        for (int i = 0; i < mark_count; i++) {
            int course_index = find_course(marks[i].course_id);
            printf("Course: %s, Student: %s, Marks: %.2f\n",
                   course_index != -1 ? courses[course_index].course_name : "Unknown",
                   marks[i].student_username, marks[i].marks);
        }
    } else if (current_role == TEACHER) {
        printf("Marks for My Courses:\n");
        for (int i = 0; i < mark_count; i++) {
            int course_index = find_course(marks[i].course_id);
            if (course_index != -1 &&
                strcmp(courses[course_index].teacher_username, current_user) == 0) {
                printf("Course: %s, Student: %s, Marks: %.2f\n",
                       courses[course_index].course_name,
                       marks[i].student_username, marks[i].marks);
            }
        }
    } else if (current_role == STUDENT) {
        printf("My Marks:\n");
        for (int i = 0; i < mark_count; i++) {
            if (strcmp(marks[i].student_username, current_user) == 0) {
                int course_index = find_course(marks[i].course_id);
                printf("Course: %s, Marks: %.2f\n",
                       course_index != -1 ? courses[course_index].course_name : "Unknown",
                       marks[i].marks);
            }
        }
    }
    
    pause_screen();
}

// Main function
int main() {
    int choice;
    
    load_data();
    
    while (1) {
        clear_screen();
        printf("=== LEARNING MANAGEMENT SYSTEM ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (login()) {
                    switch (current_role) {
                        case ADMIN: admin_menu(); break;
                        case TEACHER: teacher_menu(); break;
                        case STUDENT: student_menu(); break;
                    }
                }
                break;
            case 2:
                register_user();
                break;
            case 3:
                save_data();
                printf("Thank you for using LMS!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
                pause_screen();
                break;
        }
    }
    
    return 0;
}