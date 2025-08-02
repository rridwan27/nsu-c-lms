# 📚 Learning Management System (LMS) in C

A comprehensive command-line Learning Management System developed in C using text files for data storage. The system supports role-based authentication, course management, and educational content delivery.

## 🌟 Features

### 🔐 Authentication & Security

- User login and registration system
- Role-based access control (Admin, Teacher, Student)
- Secure credential storage in text files
- Default administrator account for system setup

### 👥 User Roles & Permissions

| Feature          | Admin | Teacher | Student |
| ---------------- | ----- | ------- | ------- |
| Login/Register   | ✅    | ✅      | ✅      |
| Create Courses   | ✅    | ❌      | ❌      |
| Add/Manage Users | ✅    | ❌      | ❌      |
| Assign Courses   | ✅    | ❌      | ❌      |
| Upload Materials | ❌    | ✅      | ❌      |
| View Materials   | ✅    | ✅      | ✅      |
| Assign Marks     | ❌    | ✅      | ❌      |
| View Marks       | ✅    | ✅      | ✅      |

### 📖 Core Functionality

- **Course Management**: Create and organize courses
- **Content Delivery**: Upload and access course materials
- **Student Enrollment**: Assign students to specific courses
- **Grading System**: Teachers can assign and track student marks
- **Data Persistence**: All data stored in organized text files

## 🚀 Quick Start

### Prerequisites

- GCC compiler
- Terminal/Command prompt access

### Installation & Setup

1. **Download the source code**

   ```bash
   # Save the LMS code as 'lms.c'
   ```

2. **Compile the program**

   ```bash
   gcc -o lms lms.c
   ```

3. **Run the application**

   ```bash
   ./lms        # Linux/Mac
   lms.exe      # Windows
   ```

4. **Login with default admin credentials**
   - **Username**: `admin`
   - **Password**: `admin123`

## 📁 File Structure

The system automatically creates and manages the following files:

```
📂 Project Directory/
├── lms.c                 # Source code
├── lms                   # Compiled executable
├── users.txt             # User accounts and roles
├── courses.txt           # Course information
├── enrollments.txt       # Student-course relationships
├── marks.txt             # Student grades
└── materials_[ID].txt    # Course-specific materials
```

### File Formats

**users.txt**

```
username password role
admin admin123 Admin
john_doe pass123 Student
jane_smith teach456 Teacher
```

**courses.txt**

```
course_id course_name teacher_username
101 Mathematics john_teacher
102 Physics jane_smith
```

**enrollments.txt**

```
course_id student_username
101 student1
101 student2
102 student1
```

**marks.txt**

```
course_id student_username marks
101 student1 85.50
102 student1 92.00
```

## 🎯 User Guide

### 🔑 Admin Functions

**Getting Started as Admin:**

1. Login with `admin`/`admin123`
2. Create courses for your institution
3. Add teachers and students
4. Assign courses to teachers
5. Enroll students in courses

**Key Admin Tasks:**

- **Create Course**: Set up new courses with unique IDs
- **Add Users**: Register new teachers and students
- **Role Management**: Change user roles as needed
- **Course Assignment**: Link teachers and students to courses
- **System Overview**: Monitor all courses, users, and grades

### 👨‍🏫 Teacher Functions

**Getting Started as Teacher:**

1. Get account from admin or register (admin must change role)
2. View assigned courses
3. Upload course materials
4. Grade student assignments

**Key Teacher Tasks:**

- **Material Upload**: Add course content and resources
- **Student Grading**: Assign marks to enrolled students
- **Progress Tracking**: Monitor student performance
- **Content Management**: Update and organize course materials

### 🎓 Student Functions

**Getting Started as Student:**

1. Register for an account
2. Wait for admin to enroll you in courses
3. Access course materials
4. Check your grades

**Key Student Tasks:**

- **Course Access**: View enrolled courses and materials
- **Grade Tracking**: Monitor academic progress
- **Resource Access**: Download and read course content

## 💡 Usage Examples

### Example Workflow

1. **Admin Setup**

   ```
   Login as admin → Create Course "Math101" → Add teacher "prof_jones"
   → Assign "Math101" to "prof_jones" → Add student "alice"
   → Enroll "alice" in "Math101"
   ```

2. **Teacher Activity**

   ```
   Login as prof_jones → View assigned courses → Upload materials to Math101
   → Assign marks to alice (score: 88.5)
   ```

3. **Student Experience**
   ```
   Login as alice → View enrolled courses → Read Math101 materials
   → Check grades (Math101: 88.5)
   ```

### Sample Data Creation

After setting up, your files might look like:

**courses.txt**

```
101 Mathematics prof_jones
102 Physics prof_smith
103 Chemistry prof_brown
```

**enrollments.txt**

```
101 alice
101 bob
102 alice
103 charlie
```

## 🛠️ Technical Details

### System Requirements

- **OS**: Linux, macOS, Windows
- **Compiler**: GCC or compatible C compiler
- **Memory**: Supports up to 100 users, 50 courses, 200 enrollments
- **Storage**: Text-file based (no database required)

### Code Architecture

- **Modular Design**: Separate functions for each feature
- **Role-Based Menus**: Dynamic interface based on user permissions
- **Data Validation**: Input verification and error handling
- **File I/O Operations**: Automatic save/load functionality

### Key Data Structures

```c
typedef struct {
    char username[50];
    char password[50];
    Role role;
} User;

typedef struct {
    int course_id;
    char course_name[100];
    char teacher_username[50];
} Course;
```

## 🔧 Customization

### Modifying Limits

Edit these constants in the source code:

```c
#define MAX_USERS 100        // Maximum number of users
#define MAX_COURSES 50       // Maximum number of courses
#define MAX_ENROLLMENTS 200  // Maximum enrollments
#define MAX_MARKS 200        // Maximum grade records
```

### Adding Features

The modular design allows easy extension:

- Add new user roles
- Implement password hashing
- Create backup systems
- Add search functionality
- Implement logging systems

## 🐛 Troubleshooting

### Common Issues

**Problem**: Files not creating

- **Solution**: Ensure write permissions in the directory
- **Check**: Run from a folder you own

**Problem**: Login fails

- **Solution**: Use default admin credentials first
- **Username**: `admin`, **Password**: `admin123`

**Problem**: Course assignment fails

- **Solution**: Ensure course exists and user has correct role
- **Check**: Admin can view all courses and users

**Problem**: Materials not showing

- **Solution**: Verify you have access to the course
- **Check**: Students must be enrolled, teachers must be assigned

### Error Messages

- `"Maximum users reached!"` → Increase MAX_USERS or remove inactive users
- `"Course not found!"` → Verify course ID exists
- `"You don't have access!"` → Check user role and course assignments

## 📈 Future Enhancements

### Planned Features

- Password encryption/hashing
- Search and filter capabilities
- Backup and restore functionality
- Grade calculation and GPA tracking
- Attendance management
- Course scheduling system
- Email notifications
- Web interface option

### Contributing

To contribute to this project:

1. Fork the repository
2. Create feature branches
3. Add comprehensive comments
4. Test with various user scenarios
5. Submit pull requests

## 📝 License

This project is open source and available under the MIT License.

## 👨‍💻 Author

Created as a comprehensive C programming project demonstrating:

- File I/O operations
- Structure-based data management
- Role-based access control
- Menu-driven program design
- Modular programming practices

---

**📞 Support**: For issues or questions, please refer to the troubleshooting section or review the source code comments for detailed implementation explanations.
