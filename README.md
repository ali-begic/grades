# Grades

**Grades** is a powerful and user-friendly cross-platform application designed for managing school grades efficiently. With a sleek and intuitive UI built using the Qt framework, it offers comprehensive features to handle all aspects of grade management. Users can easily add, update, and remove subjects and grades, view detailed reports, and export data as needed. The application ensures smooth operation with customizable options for handling grades and subjects, making it an essential tool for students and educators alike.

![grades-capture](https://github.com/user-attachments/assets/910d9ceb-5489-49a1-a1a8-cdfc7555a3aa)

## Features of the Grades Qt Application

### Cross-Platform Compatibility
- Works seamlessly across different operating systems, making it accessible to a wide range of users.

### Sleek and Intuitive User Interface
- Built with the Qt framework, the application offers a visually appealing and user-friendly interface, making navigation and usage simple and efficient.

### Comprehensive Grade Management
- **Add Subjects**: Easily add new subjects to the grade management system.
- **Update Grades**: Modify existing grades for subjects with ease.
- **Remove Subjects and Grades**: Quickly remove subjects or individual grades from the system.

### Detailed Reports
- **View Grades**: Access detailed views of all grades associated with each subject.
- **Grade Summary**: Get an overview of the average grades, along with a "Prolazna ocjena" (passing grade) that corresponds to the average.

### Data Exporting
- **Export Reports**: Export grade reports to various formats or locations, making it easy to share or back up data.

### Keyboard Shortcuts
- Use keyboard shortcuts to enhance productivity, such as connecting specific keys to frequently used functions.

### Real-Time Updates
- Immediate reflection of changes in the UI when grades or subjects are added, updated, or removed.

### Error Handling and Validation
- **Empty Input Validation**: Prevent errors by validating inputs, ensuring that no empty fields are submitted.
- **Confirmation Dialogs**: Provide confirmation prompts before performing irreversible actions like deleting subjects or grades.

These features make the **Grades** a robust tool for efficiently managing school grades, tailored to the needs of students and educators.

## Building the Qt Application from Source

To build and run the **Grades** application from source, it would be best solution to open the application in [Qt Creator](https://www.qt.io/), then compile it to your liking. But if you want to do it manually, here are the steps you need to follow: 

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
     - [Qt Documentation for Windows](https://doc.qt.io/qt-6/windows-deployment.html)
     - [Qt Documentation for macOS](https://doc.qt.io/qt-6/macos-deployment.html)
     - [Qt Documentation for Linux](https://doc.qt.io/qt-6/linux-deployment.html)

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
   - Compile the application:
      - On Windows with MSVC:
        ```
        nmake
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

## Using `windeployqt` for Windows Deployment

To deploy the **Grades** application on Windows, you can use the `windeployqt` tool. This tool automatically copies the necessary Qt runtime files (DLLs, plugins, etc.) to your application's deployment folder, making it easier to distribute the application.

### Steps to Use `windeployqt`:

1. **Build Your Application:**
   - Ensure that your application is fully built using the steps above.

2. **Open the Correct Command Prompt:**
   - Open the "Developer Command Prompt for VS 2022" or the "Qt MinGW" command prompt, depending on the compiler you used.

3. **Navigate to the Build Directory:**
   - Use the command prompt to navigate to the directory where your application’s executable is located:
     ```bash
     cd ../grades/build/release
     ```

4. **Run `windeployqt`:**
   - Run the following command to deploy your application:
     ```bash
     windeployqt grades.exe
     ```

5. **Test the Deployed Application:**
   - After running `windeployqt`, test the application by running the executable in its deployment directory to ensure all dependencies are correctly deployed.

6. **Distribute the Application:**
   - You can now package the deployed files (including the executable and all copied DLLs and plugins) into a ZIP file, installer, or other distribution formats for distribution.

## Contributing

Contributions are welcome! If you find a bug, have a feature request, or want to improve the code, feel free to open an issue or submit a pull request.

## License

This project is licensed under the Apache-2.0 license - see the [LICENSE](LICENSE) file for details.

## Additional Notes

- Ensure that you have the correct version of Qt and associated build tools for your platform.
- If you encounter issues, check the Qt and compiler documentation or seek assistance on community forums.
- If the application still does not work properly, try running it as an administrator.

Thank you for your interest in the **Grades** application!
