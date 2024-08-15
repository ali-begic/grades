# Grades

Grades is a powerful and user-friendly application designed for managing school grades efficiently. With a sleek and intuitive UI built using the Qt framework, it offers comprehensive features to handle all aspects of grade management. Users can easily add, update, and remove subjects and grades, view detailed reports, and export data as needed. The application ensures smooth operation with customizable options for handling grades and subjects, making it an essential tool for students and educators alike.

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
     - Qt Documentation for Windows
     - Qt Documentation for macOS
     - Qt Documentation for Linux

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
   - Compile the application using `nmake` for MSVC (or `mingw32-make` for MinGW):
     ```
     nmake
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

Thank you for your interest in the Grades application!

---

**Deploying on Windows with `windeployqt`:**

1. **Locate Your Executable:**
   - Make sure your application has been built successfully, and you have the executable (e.g., `grades.exe`) in your build directory.

2. **Open a Command Prompt:**
   - Open a command prompt or terminal window.

3. **Navigate to the Build Directory:**
   - Use the `cd` command to navigate to the directory where your executable is located. For example:
     ```
     cd path/to/your/build/directory
     ```

4. **Run `windeployqt`:**
   - Execute the following command, replacing `grades.exe` with your actual executable name:
     ```
     windeployqt grades.exe
     ```

5. **Check the Deployed Files:**
   - `windeployqt` will analyze your application and copy the necessary Qt libraries and plugins to the same directory as your executable.
   - You'll find additional files like DLLs, plugins, and resources alongside your executable.

6. **Test Your Deployed Application:**
   - Run your application from the same directory to ensure that it works correctly with the bundled Qt dependencies.

Remember that `windeployqt` automatically detects the required Qt modules and copies them. If you encounter any issues, refer to the official documentation for more details.
