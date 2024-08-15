/*
 * Copyright 2024 AliTech Works
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QShortcut>

QFile file("grades.txt");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QString statusBarMessage = "Grades - by AliTech Works v1.0";
    ui->statusBar->setSizeGripEnabled(false);
    ui->statusBar->setStyleSheet("border-top: 1px outset grey;");
    ui->statusBar->showMessage(statusBarMessage);

    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    } else {
        loadInformation();
        updateOverallAverageLabel();
    }

    ui->grades_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set fixed width for the first column and stretch mode for the others
    ui->grades_tableWidget->setColumnWidth(0, 180);

    QHeaderView *header = ui->grades_tableWidget->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Fixed);   // Fixed width for column 0
    header->setSectionResizeMode(1, QHeaderView::Stretch); // Stretch mode for other columns

    connect(ui->grades_tableWidget, &QTableWidget::itemClicked, this, &MainWindow::showStatus);
    connect(ui->grades_tableWidget, &QTableWidget::currentCellChanged, this, &MainWindow::updateSelectedSubjectLabel);
    connect(ui->grades_tableWidget, &QTableWidget::cellDoubleClicked, this, [this](int row, int column) {
        QTableWidgetItem *item = ui->grades_tableWidget->item(row, column);

        if (column == 0 && item && !item->text().isEmpty())
            on_grades_pushButton_clicked();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadInformation() {
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString currentSubject;

        QTextStream input(&file);
        while (!input.atEnd()) {
            QString line = input.readLine();

            if (line.startsWith("Subject: ")) {
                currentSubject = line.mid(9);

                addSubject(currentSubject);
            } else if (line.startsWith("Average: ")) {
                for (int row = 0; row < ui->grades_tableWidget->rowCount(); ++row) {
                    QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0); // Column 0 is for names
                    if (item && item->text() == currentSubject) {
                        QTableWidgetItem *averageItem = new QTableWidgetItem(line.mid(9));

                        averageItem->setTextAlignment(Qt::AlignCenter);
                        ui->grades_tableWidget->setItem(row, 1, averageItem); // Column 1 is for Average

                        break;
                    }
                }
            } else if (line.startsWith("Passing grade: ")) {
                for (int row = 0; row < ui->grades_tableWidget->rowCount(); ++row) {
                    QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0); // Column 0 is for names

                    if (item && item->text() == currentSubject) {
                        QTableWidgetItem *passingGradeItem = new QTableWidgetItem(line.mid(15));

                        passingGradeItem->setTextAlignment(Qt::AlignCenter);
                        ui->grades_tableWidget->setItem(row, 2, passingGradeItem); // Column 2 is for Passing grade

                        break;
                    }
                }
            }
        }

        file.close();
    }
}

void MainWindow::updateOverallAverageLabel() {
    // Variables to hold the sum and count of values
    int sum = 0;
    int count = 0;

    // Iterate through all rows in the "Prosjek" column
    for (int row = 0; row < ui->grades_tableWidget->rowCount(); row++) {
        QTableWidgetItem *item = ui->grades_tableWidget->item(row, 1);

        if (item && !item->text().isEmpty()) {
            double value = item->text().toDouble();

            sum += std::round(value);

            count++;
        }
    }

    // Calculate the average using the whole parts
    double average = (count > 0) ? static_cast<double>(sum) / count : 0.0;

    // Update the label with the average
    if (average != 0)
        ui->overallAverage_label->setText(QString("OVERALL AVERAGE: %1").arg(average, 0, 'f', 2));
    else
        ui->overallAverage_label->setText(QString("OVERALL AVERAGE: "));
}

void MainWindow::addSubject(QString name) {
    int numberOfRows = ui->grades_tableWidget->rowCount();

    // Find the first empty row to add the new item
    int rowToAdd = -1;
    for (int row = 0; row < numberOfRows; row++) {
        QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0);

        if (!item || item->text().isEmpty()) {
            rowToAdd = row;

            break;
        }
    }

    // If no empty row is found, add a new row
    if (rowToAdd == -1) {
        rowToAdd = numberOfRows;
        ui->grades_tableWidget->setRowCount(numberOfRows + 1);
    }

    // Add the new item
    QTableWidgetItem *item = new QTableWidgetItem(name);
    ui->grades_tableWidget->setItem(rowToAdd, 0, item);

    for (int row = 0; row <= rowToAdd; ++row) {
        QTableWidgetItem *numberItem = new QTableWidgetItem(QString::number(row + 1) + ".");
        ui->grades_tableWidget->setVerticalHeaderItem(row, numberItem);
    }

    ui->grades_tableWidget->sortItems(0, Qt::AscendingOrder);
}

void MainWindow::showStatus(QTableWidgetItem *item) {
    // Return if the "Subject" column is not selected
    if (item->column() > 0) {
        return;
    }

    if (item && !item->text().isEmpty()) {
        ui->subject_label->setText(item->text());
        ui->subject_label->setAlignment(Qt::AlignCenter);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString currentSubject;

            QTextStream input(&file);
            while (!input.atEnd()) {
                QString line = input.readLine();

                if (line.startsWith("Subject: ")) {
                    currentSubject = line.mid(9);
                } else if (item->text() == currentSubject && line.startsWith("Grades: ")) {
                    ui->grades_label->setText(line);
                } else if (item->text() == currentSubject && line.startsWith("Average: ")) {
                    ui->average_label->setText(line);
                } else if (item->text() == currentSubject && line.startsWith("Number of grades: ")) {
                    ui->numberOfGrades_label->setText(line);
                }
            }

            file.close();
        }
    }
}

void MainWindow::on_addSubject_mainWindow_clicked() {
    QDialog addSubjectWindow;
    addSubjectWindow.setFixedSize(300, 100);
    addSubjectWindow.setWindowTitle("Add subject");
    addSubjectWindow.setWindowIcon(QIcon(":/icons/grades.ico"));

    QVBoxLayout mainLayout;
    QHBoxLayout horizontalLayout1;
    QHBoxLayout horizontalLayout2;

    QLabel nameLabel("Subject name:");
    QLineEdit nameInputField;

    QPushButton addButton("Add");
    addButton.setFocusPolicy(Qt::NoFocus);

    auto addSubjectLambda = [this, &addSubjectWindow, &nameInputField]() {
        QString subjectName = nameInputField.text();

        if (subjectName.isEmpty()) {
            QMessageBox::warning(&addSubjectWindow, "Input Error", "The subject name cannot be empty!");
        } else if (subjectName.length() > 30) {
            QMessageBox::warning(&addSubjectWindow, "Input Error", "The subject name cannot be longer than 30 characters!");
        } else {
            int numberOfRows = ui->grades_tableWidget->rowCount();

            for (int row = 0; row < numberOfRows; row++) {
                QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0);
                if (item && item->text() == subjectName) {
                    QMessageBox::warning(&addSubjectWindow, "Duplicate Entry", "'" + subjectName + "' subject already exists!");

                    return;
                }
            }

            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream output(&file);

                file.seek(file.size());

                if (file.size() > 0) {
                    file.seek(file.size() - 1);

                    char lastChar;
                    file.getChar(&lastChar);

                    if (lastChar != '\n') {
                        output << "\n";
                    }
                }

                output << "Subject: " << subjectName << "\n";
                output << "Grades: " << "\n";
                output << "Average: " << "\n";
                output << "Number of grades: " << "\n";
                output << "Passing grade: " << "\n";

                file.close();
            }

            addSubject(subjectName);
            nameInputField.clear();
        }
    };

    connect(&addButton, &QPushButton::clicked, addSubjectLambda);
    connect(&nameInputField, &QLineEdit::returnPressed, addSubjectLambda);

    QPushButton closeButton("Close");
    closeButton.setFocusPolicy(Qt::NoFocus);
    connect(&closeButton, &QPushButton::clicked, &addSubjectWindow, &QDialog::close);

    horizontalLayout1.addWidget(&nameLabel);
    horizontalLayout1.addWidget(&nameInputField);

    horizontalLayout2.addWidget(&addButton);
    horizontalLayout2.addWidget(&closeButton);

    mainLayout.addLayout(&horizontalLayout1);
    mainLayout.addItem(new QSpacerItem(20, 10));
    mainLayout.addLayout(&horizontalLayout2);

    addSubjectWindow.setLayout(&mainLayout);
    addSubjectWindow.exec();
}

void MainWindow::on_removeSubject_mainWindow_clicked() {
    QString selectedItem = ui->subject_label->text();

    if (selectedItem.contains("SUBJECT")) {
        QMessageBox::warning(this, "Selection Error", "Please select the subject to remove it!");

        return;
    }

    QMessageBox::StandardButton confirmationMessage;
    confirmationMessage = QMessageBox::question(this, "Warning", "Are you sure you want to remove this subject?");

    if (confirmationMessage != QMessageBox::Yes)
        return;

    // Remove the subject from the table widget
    int selectedRow = -1;
    for (int row = 0; row < ui->grades_tableWidget->rowCount(); row++) {
        QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0);

        if (item && item->text() == selectedItem) {
            selectedRow = row;

            QTableWidgetItem *nextItem = ui->grades_tableWidget->item(row + 1, 0);
            if (nextItem) {

                showStatus(nextItem);
            } else {
                ui->subject_label->setText("SUBJECT");
                ui->grades_label->setText("Grades: ");
                ui->average_label->setText("Average: ");
                ui->numberOfGrades_label->setText("Number of grades: ");
            }

            break;
        }
    }

    if (selectedRow != -1) {
        ui->grades_tableWidget->setItem(selectedRow, 0, nullptr);

        // Shift items up
        for (int row = selectedRow; row < ui->grades_tableWidget->rowCount() - 1; ++row) {
            QTableWidgetItem *currentItem = ui->grades_tableWidget->item(row + 1, 0);

            if (currentItem) {
                QTableWidgetItem *newItem = new QTableWidgetItem(currentItem->text());
                ui->grades_tableWidget->setItem(row, 0, newItem);
            } else {
                ui->grades_tableWidget->setItem(row, 0, nullptr);
            }

            // Shift the corresponding "Average" row
            QTableWidgetItem *averageItem = ui->grades_tableWidget->item(row + 1, 1);

            if (averageItem) {
                QTableWidgetItem *newAverageItem = new QTableWidgetItem(averageItem->text());

                newAverageItem->setTextAlignment(Qt::AlignCenter); // Align center
                ui->grades_tableWidget->setItem(row, 1, newAverageItem);
            } else {
                ui->grades_tableWidget->setItem(row, 1, nullptr);
            }

            // Shift the corresponding "Passing grade" row
            QTableWidgetItem *passingGradeItem = ui->grades_tableWidget->item(row + 1, 2);

            if (passingGradeItem) {
                QTableWidgetItem *newPassingGradeItem = new QTableWidgetItem(passingGradeItem->text());

                newPassingGradeItem->setTextAlignment(Qt::AlignCenter); // Align center
                ui->grades_tableWidget->setItem(row, 2, newPassingGradeItem);
            } else {
                ui->grades_tableWidget->setItem(row, 2, nullptr);
            }
        }

        // Clear the last row items
        ui->grades_tableWidget->setItem(ui->grades_tableWidget->rowCount() - 1, 0, nullptr);
        ui->grades_tableWidget->setItem(ui->grades_tableWidget->rowCount() - 1, 1, nullptr);
        ui->grades_tableWidget->setItem(ui->grades_tableWidget->rowCount() - 1, 2, nullptr);

        if (ui->grades_tableWidget->rowCount() > 10)
            ui->grades_tableWidget->setRowCount(ui->grades_tableWidget->rowCount() - 1);

        // Update the grades.txt file
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream input(&file);
            QStringList lines;
            QString currentSubject;
            bool subjectFound = false;

            // Read the existing file content
            while (!input.atEnd()) {
                QString line = input.readLine();

                if (line.startsWith("Subject: ")) {
                    currentSubject = line.mid(9);
                    subjectFound = (currentSubject == selectedItem);

                    if (!subjectFound) {
                        if (!lines.isEmpty() && !lines.last().isEmpty())
                            lines.append(""); // Ensure a blank line before each new subject

                        lines.append(line); // Add the Predmet line if it's not the one to be removed
                    }
                } else if (!subjectFound) {
                    lines.append(line); // Add all other lines that are not part of the subject to be removed
                }
            }

            file.close();

            // Remove trailing blank lines if any
            while (!lines.isEmpty() && lines.last().isEmpty()) {
                lines.removeLast();
            }

            // Reopen the file in write-only mode to update its contents
            if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                QTextStream output(&file);

                for (const QString &line : lines) {
                    output << line << "\n";
                }

                file.close();
            }
        }
    }

    updateOverallAverageLabel();
}

void MainWindow::on_grades_pushButton_clicked() {
    if (ui->subject_label->text().contains("SUBJECT")) {
        QMessageBox::warning(this, tr("Error"), tr("No item selected!"));

        return;
    }

    QDialog subjectWindow;
    subjectWindow.setFixedSize(300, 165);
    subjectWindow.setWindowTitle(ui->subject_label->text());
    subjectWindow.setWindowIcon(QIcon(":/icons/grades.ico"));

    QVBoxLayout mainLayout;
    QVBoxLayout verticalLayout1;
    QHBoxLayout horizontalLayout1;
    QHBoxLayout horizontalLayout2;

    QLabel gradesString("Grades: ");
    QLabel averageLabel("Average: ");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString currentSubject;

        QTextStream input(&file);

        while (!input.atEnd()) {
            QString line = input.readLine();

            if (line.startsWith("Subject: ")) {
                currentSubject = line.mid(9);
            } else if (ui->subject_label->text() == currentSubject && line.startsWith("Grades: ")) {
                gradesString.setText(line);
            } else if (ui->subject_label->text() == currentSubject && line.startsWith("Average: ")) {
                averageLabel.setText(line);
            }
        }

        file.close();
    }

    verticalLayout1.addWidget(&gradesString);
    verticalLayout1.addWidget(&averageLabel);
    verticalLayout1.addItem(new QSpacerItem(20, 10));

    QPushButton button_1("1");
    QPushButton button_2("2");
    QPushButton button_3("3");
    QPushButton button_4("4");
    QPushButton button_5("5");

    button_1.setFocusPolicy(Qt::NoFocus);
    button_2.setFocusPolicy(Qt::NoFocus);
    button_3.setFocusPolicy(Qt::NoFocus);
    button_4.setFocusPolicy(Qt::NoFocus);
    button_5.setFocusPolicy(Qt::NoFocus);

    horizontalLayout1.addWidget(&button_1);
    horizontalLayout1.addWidget(&button_2);
    horizontalLayout1.addWidget(&button_3);
    horizontalLayout1.addWidget(&button_4);
    horizontalLayout1.addWidget(&button_5);

    QPushButton backspaceButton("Backspace");
    backspaceButton.setFocusPolicy(Qt::NoFocus);

    QPushButton okButton("OK");
    okButton.setFocusPolicy(Qt::NoFocus);
    QPushButton cancelButton("Cancel");
    cancelButton.setFocusPolicy(Qt::NoFocus);

    horizontalLayout2.addWidget(&okButton);
    horizontalLayout2.addWidget(&cancelButton);

    verticalLayout1.addLayout(&horizontalLayout1);
    verticalLayout1.addWidget(&backspaceButton);
    verticalLayout1.addItem(new QSpacerItem(20, 10)); // Added spacer directly
    verticalLayout1.addLayout(&horizontalLayout2);
    mainLayout.addLayout(&verticalLayout1);

    subjectWindow.setLayout(&mainLayout);

    // List to store grades
    QList<int> grades;
    double average = 0.0;

    // Parse existing grades from gradesString
    QString gradesListString = gradesString.text().mid(8); // Skip the "Grades: " part
    QStringList gradesList = gradesListString.split(", ", Qt::SkipEmptyParts);

    for (const QString &gradeString : gradesList) {
        int grade = gradeString.toInt();

        grades.append(grade);
    }

    // Parse existing average from averageLabel
    QStringList averageList = averageLabel.text().split(": ");
    if (averageList.size() > 1) {
        average = averageList[1].toDouble();
    }

    // Create the updateLabels function
    auto updateLabels = [&gradesString, &averageLabel, &grades, &average]() {
        double sum = 0;
        QStringList gradesStrings;

        for (int grade : grades) {
            gradesStrings << QString::number(grade);
            sum += grade;
        }

        gradesString.setText("Grades: " + gradesStrings.join(", "));
        average = (grades.isEmpty()) ? 0 : sum / grades.size();

        if (average != 0)
            averageLabel.setText("Average: " + QString::number(average, 'f', 2));
        else
            averageLabel.setText("Average: ");
    };

    // Initialize labels
    updateLabels();

    // Mouse click function
    auto buttonConnect = [&grades, &updateLabels](QPushButton &button, int grade) {
        QObject::connect(&button, &QPushButton::clicked, [&grades, &updateLabels, grade]() {
            grades.append(grade);
            updateLabels();
        });
    };

    buttonConnect(button_1, 1);
    buttonConnect(button_2, 2);
    buttonConnect(button_3, 3);
    buttonConnect(button_4, 4);
    buttonConnect(button_5, 5);

    // Functionality for backspace button (remove last grade)
    QObject::connect(&backspaceButton, &QPushButton::clicked, [&grades, &updateLabels]() {
        if (!grades.isEmpty()) {
            grades.removeLast();
            updateLabels();
        }
    });

    // Create shortcuts
    auto createShortcut = [&subjectWindow, &grades, updateLabels](Qt::Key key, int grade) {
        QString keySequence = QKeySequence(key).toString();
        QShortcut *shortcut = new QShortcut(QKeySequence(keySequence), &subjectWindow);

        QObject::connect(shortcut, &QShortcut::activated, [&grades, updateLabels, grade]() {
            grades.append(grade);
            updateLabels();
        });

        shortcut->setContext(Qt::ApplicationShortcut);  // Ensure shortcuts work globally within the app
    };

    createShortcut(Qt::Key_1, 1);
    createShortcut(Qt::Key_2, 2);
    createShortcut(Qt::Key_3, 3);
    createShortcut(Qt::Key_4, 4);
    createShortcut(Qt::Key_5, 5);

    auto backspaceShortcut = new QShortcut(QKeySequence(Qt::Key_Backspace), &subjectWindow);
    QObject::connect(backspaceShortcut, &QShortcut::activated, [&grades, updateLabels]() {
        if (!grades.isEmpty()) {
            grades.removeLast();
            updateLabels();
        }
    });

    auto submit = [&]() {
        if (average != 0 && grades.size() != 0) {
            ui->grades_label->setText(gradesString.text());
            ui->numberOfGrades_label->setText("Number of grades: " + QString::number(grades.size()));
            ui->average_label->setText("Average: " + QString::number(average, 'f', 2));
        } else {
            ui->grades_label->setText("Grades: ");
            ui->average_label->setText("Average: ");
            ui->numberOfGrades_label->setText("Number of grades: ");
        }

        // Update the Average and the Passing grade column in the tableWidget
        for (int row = 0; row < ui->grades_tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->grades_tableWidget->item(row, 0);

            if (item && item->text() == ui->subject_label->text()) {
                if (average != 0) {
                    QTableWidgetItem *averageItem = new QTableWidgetItem(QString::number(average, 'f', 2));

                    averageItem->setTextAlignment(Qt::AlignCenter);
                    ui->grades_tableWidget->setItem(row, 1, averageItem);

                    QTableWidgetItem *passingGradeItem = new QTableWidgetItem();

                    if (average >= 1.00 && average < 1.50)
                        passingGradeItem->setText("Insufficient");
                    else if (average >= 1.50 && average < 2.50)
                        passingGradeItem->setText("Sufficient");
                    else if (average >= 2.50 && average < 3.50)
                        passingGradeItem->setText("Good");
                    else if (average >= 3.50 && average < 4.50)
                        passingGradeItem->setText("Very Good");
                    else if (average >= 4.50 && average <= 5.00)
                        passingGradeItem->setText("Excellent");

                    passingGradeItem->setTextAlignment(Qt::AlignCenter);
                    ui->grades_tableWidget->setItem(row, 2, passingGradeItem);
                } else {
                    QTableWidgetItem *averageItem = new QTableWidgetItem("");
                    QTableWidgetItem *passingGradeItem = new QTableWidgetItem("");

                    ui->grades_tableWidget->setItem(row, 1, averageItem);
                    ui->grades_tableWidget->setItem(row, 2, passingGradeItem);
                }

                break;
            }
        }

        // Update the "grades.txt" file
        bool subjectFound = false;
        QStringList lines;
        QString currentSubject;
        QString subjectLabel = ui->subject_label->text();

        // Read the existing file content
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString previousLine;

            QTextStream input(&file);

            while (!input.atEnd()) {
                QString line = input.readLine();

                if (line.startsWith("Subject: ")) {
                    currentSubject = line.mid(9);
                    subjectFound = (currentSubject == subjectLabel);

                    if (!previousLine.isEmpty() && !previousLine.endsWith('\n')) {
                        lines.append(""); // Add a newline before each new subject
                    }

                    lines.append(line); // Add the Subject line
                } else if (subjectFound && line.startsWith("Grades: ")) {
                    lines.append(gradesString.text());

                    subjectFound = false; // We have handled the subject, reset the flag
                } else if (currentSubject == subjectLabel && line.startsWith("Average: ")) {
                    lines.append(ui->average_label->text());
                } else if (currentSubject == subjectLabel && line.startsWith("Number of grades: ")) {
                    lines.append(ui->numberOfGrades_label->text());
                } else if (currentSubject == subjectLabel && line.startsWith("Passing grade: ")) {
                    QStringView numericPart = QStringView(ui->average_label->text()).mid(9);
                    double average = numericPart.toDouble();

                    if (average >= 1.00 && average < 1.50)
                        lines.append("Passing grade: Insufficient");
                    else if (average >= 1.50 && average < 2.50)
                        lines.append("Passing grade: Sufficient");
                    else if (average >= 2.50 && average < 3.50)
                        lines.append("Passing grade: Good");
                    else if (average >= 3.50 && average < 4.50)
                        lines.append("Passing grade: Very Good");
                    else if (average >= 4.50 && average <= 5.00)
                        lines.append("Passing grade: Excellent");
                } else {
                    lines.append(line); // Add all other lines
                }

                previousLine = line;
            }

            file.close();
        }

        // Write the updated content back to the file
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream output(&file);

            for (const QString& line : lines) {
                output << line << "\n";
            }

            file.close();
        }

        updateOverallAverageLabel();
        subjectWindow.close();
    };

    auto enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), &subjectWindow);
    QObject::connect(enterShortcut, &QShortcut::activated, [submit = submit]() { submit(); });

    QObject::connect(&okButton, &QPushButton::clicked, this, submit);

    QObject::connect(&cancelButton, &QPushButton::clicked, &subjectWindow, &QDialog::close);

    subjectWindow.exec();
}

void MainWindow::on_export_pushButton_clicked() {
    // Static regular expressions to avoid creating them repeatedly
    static const QRegularExpression removeBlankLinesRegex("\\n\\s*\\n");
    static const QRegularExpression addBlankLineRegex("(?<!^)(?<=\\n)(?=Subject: )");

    // Create a QFileDialog to let the user select a file location
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));

    // Check if the user selected a file
    if (fileName.isEmpty()) {
        return; // User canceled the dialog, do nothing
    }

    // Open the "grades.txt" file for reading
    QFile inputFile("grades.txt");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open 'grades.txt' for reading."));

        return;
    }

    // Read the contents of "grades.txt"
    QTextStream input(&inputFile);
    QString content = input.readAll();

    inputFile.close();

    // Create the new content with the "Overall average: " line at the beginning
    QString newContent = "Overall average: " + ui->overallAverage_label->text().mid(17) + "\n\n" + content;

    // Remove extra blank lines, ensuring only one blank line before each "Subject: "
    newContent.replace(removeBlankLinesRegex, "\n");
    newContent.replace(addBlankLineRegex, "\n");

    // Open the selected file for writing
    QFile outputFile(fileName);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open the selected file for writing."));

        return;
    }

    // Write the new content to the selected file
    QTextStream output(&outputFile);
    output << newContent;
    outputFile.close();
}
