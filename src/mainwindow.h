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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addSubject_mainWindow_clicked();

    void on_removeSubject_mainWindow_clicked();

    void on_grades_pushButton_clicked();

    void on_export_pushButton_clicked();

    void updateSelectedSubjectLabel(int currentRow, int currentColumn, int previousRow, int previousColumn) {
        QTableWidgetItem *currentItem = ui->grades_tableWidget->item(currentRow, 0); // Assuming the subject is in the first column

        if (currentItem) {
            showStatus(currentItem);
        } else {
            ui->subject_label->setText("SUBJECT");
            ui->subject_label->setAlignment(Qt::AlignCenter);

            ui->grades_label->setText("Grades: ");
            ui->average_label->setText("Average: ");
            ui->numberOfGrades_label->setText("Number of grades: ");
        }
    }

private:
    Ui::MainWindow *ui;

    void loadInformation();
    void updateOverallAverageLabel();
    void addSubject(QString name);
    void showStatus(QTableWidgetItem *item);

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Delete) {
            // Call the function when 'delete' key is pressed
            on_removeSubject_mainWindow_clicked();
        } else if (event->key() == Qt::Key_Return || event->key() ==  Qt::Key_Enter) {
            // Call the function when 'enter' key is pressed
            on_grades_pushButton_clicked();
        } else {
            // Call the base class implementation for other keys
            QWidget::keyPressEvent(event);
        }
    }
};
#endif // MAINWINDOW_H
