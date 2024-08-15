# Grades

Grades is a powerful and user-friendly application designed for managing school grades efficiently. With a sleek and intuitive UI built using the Qt framework, it offers comprehensive features to handle all aspects of grade management. Users can easily add, update, and remove subjects and grades, view detailed reports, and export data as needed. The application ensures smooth operation with customizable options for handling grades and subjects, making it an essential tool for students and educators alike.

## Building the Qt Application from Source

1. **Clone the Repository:**
   - First, ensure you have Git installed on your system.
   - Open your terminal or command prompt and navigate to the directory where you want to clone your repository.
   - Run the following command to clone your repository:
     ```bash
     git clone https://github.com/ali-begic/grades
     ```

2. **Install Qt Dependencies:**
   - Before building your application, make sure you have the necessary dependencies installed. These include Qt libraries, compilers, and build tools.
   - Refer to the official Qt documentation for platform-specific instructions:
     - Building Qt Sources for Windows
     - Building Qt Sources for macOS
     - Building Qt Sources for Linux/X11
     - Building Qt Sources for Android
     - Building Qt Sources for iOS

3. **Configure and Build:**
   - Once dependencies are set up, navigate to your cloned repository directory.
   - Run the following commands to configure and build your application:
     ```bash
     mkdir build
     cd build
     qmake ..
     make
     ```
   - Adjust the `qmake` command if your project uses a specific `.pro` file.

4. **Run Your Application:**
   - After successful compilation, you'll find the executable in the `build` directory.
   - Run your application using:
     ```bash
     ./grades
     ```
