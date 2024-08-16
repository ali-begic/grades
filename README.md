# Grades

Grades is a powerful and user-friendly cross-platform application designed for managing school grades efficiently. With a sleek and intuitive UI built using the Qt framework, it offers comprehensive features to handle all aspects of grade management. Users can easily add, update, and remove subjects and grades, view detailed reports, and export data as needed. The application ensures smooth operation with customizable options for handling grades and subjects, making it an essential tool for students and educators alike.

## Building the Qt Application from Source

To build and run the Grades application from source, follow these steps:

1. **Clone the Repository:**
   - Ensure you have Git installed on your system.
   - Open your terminal or command prompt and navigate to the directory where you want to clone the repository.
   - Run the following command:
     ```
     git clone https://github.com/ali-begic/grades
     ```
   - Navigate into the cloned directory:
     ```
     cd grades
     ```

2. **Install Qt Dependencies:**
   - Ensure you have the necessary Qt libraries, compilers, and build tools installed. Refer to the official Qt documentation for platform-specific instructions:
     - Qt Documentation for Windows [Qt Documentation for Windows](https://doc.qt.io/qt-5/windows-deployment.html)
     - Qt Documentation for macOS [Qt Documentation for macOS](https://doc.qt.io/qt-5/macos-deployment.html)
     - Qt Documentation for Linux [Qt Documentation for Linux](https://doc.qt.io/qt-5/linux-deployment.html)

3. **Configure and Build:**
   - Create a build directory and navigate into it:
     ```
     mkdir build
     cd build
     ```
   - Run `qmake` to generate the Makefile from the `.pro` file:
     ```
     qmake ../src/grades.pro
     ```
   - On Windows with MSVC:
     ```
     nmake
     ```
   - On Windows with MinGW:
     ```
     mingw32-make
     ```
   - On Windows with MinGW:
     ```
     mingw32-make
     ```
   - On macOS and Linux:
     ```
     make
     ```

4. **Run Your Application:**
   - After a successful build, the executable will be located in the build directory.
   - Run the application:
     ```
     ./grades
     ```
   - On Windows, you can find the executable in the release or debug directory depending on your build configuration.

## Additional Notes

- Ensure that you have the correct version of Qt and associated build tools for your platform.
- If you encounter issues, check the Qt and compiler documentation or seek assistance on community forums.
- If the application still does not work properly, try running it as an administrator.

Thank you for your interest in the Grades application!
