#include "MainWindow.hpp"

void MainWindow::initObjects() {
    mainLayout      = new QVBoxLayout(this);
    codeSegment     = new QGroupBox("Solution");
    options         = new QGroupBox("What now?");
    testCases       = new QGroupBox("Test Cases");
    testCasesLayout = new QVBoxLayout(testCases);
}

void MainWindow::setupMainLayout() {
    mainLayout->addWidget(codeSegment);
    mainLayout->addWidget(options);
    mainLayout->addWidget(testCases);
}

void MainWindow::setupCodeSegment() {
    compilationMethod = new QComboBox;
    compilationMethod->setToolTip("Language");
    compilationMethod->insertItem(0, "C", "gcc");
    compilationMethod->insertItem(1, "C++", "g++");

    code = new QPlainTextEdit;
    code->setFont(QFont("Ubuntu Mono"));
    code->setPlaceholderText("Your code...");
    code->setWordWrapMode(QTextOption::NoWrap);

    codeSegmentLayout = new QVBoxLayout(codeSegment);
    codeSegmentLayout->addWidget(compilationMethod);
    codeSegmentLayout->addWidget(code);
}

void MainWindow::setupOptions() {
    addTestCase     = new QPushButton("Add a Test Case");
    generateOutputs = new QPushButton("Generate the Outputs");
    dragZipArchive  = new DraggableButton("Zip");
    dragZipArchive->setToolTip("Drag and Drop me!");

    optionsLayout = new QHBoxLayout(options);
    optionsLayout->addWidget(addTestCase);
    optionsLayout->addWidget(generateOutputs);
    optionsLayout->addWidget(dragZipArchive);
}

void MainWindow::setupTestCases() {
    testCasesScroll = new QScrollArea();
    testCasesScroll->setWidgetResizable(true);
    testCasesFrame = new QFrame(testCasesScroll);
    testCasesList = new QVBoxLayout(testCasesFrame);
    testCasesScroll->setWidget(testCasesFrame);
    testCasesLayout->addWidget(testCasesScroll);
}

void MainWindow::newTestCase() {
    auto ptr = new TestCase(testCaseIndex++);
    connect(ptr, &TestCase::isRemoved, this, &MainWindow::removeTestCase);
    testCasesList->addWidget(ptr);
}

void MainWindow::removeTestCase(int index) {
    for (int i(0); i < testCasesList->count(); i++) {
        auto item = dynamic_cast<TestCase*>(testCasesList->itemAt(i)->widget());
        if (item->index == index) {
            disconnect(item, &TestCase::isRemoved, this, &MainWindow::removeTestCase);
            testCasesList->removeWidget(item);
            item->deleteLater();
            return;
        }
    }
}

void MainWindow::generateFiles() {
    // Let's do a quick check!
    if (testCasesList->count() == 0) {
        QMessageBox noTestCases(QMessageBox::Warning, "What the?!", "Dude, you haven't defined any test cases!", QMessageBox::Ok);
        noTestCases.setInformativeText("What the hell am I supposed to give to your program?!");
        noTestCases.exec();
        return;
    }

    // Frequently used addresses
    QString workingDirectory(QDir::currentPath() + "/problem/");
    QString codeFileName(compilationMethod->currentIndex() == 0 ? "code.c" : "code.cpp");

    // Create the folders
    system(("rm -r -f \"" + workingDirectory + '\"').toLocal8Bit().data());
    system(("mkdir \"" + workingDirectory + '\"').toLocal8Bit().data());
    system(("mkdir \"" + workingDirectory + "in\" \"" + workingDirectory + "out\"").toLocal8Bit().data());

    // Write down the code
    QFile codeFile(workingDirectory + codeFileName);
    QTextStream codeStream(&codeFile);
    codeFile.open(QIODevice::WriteOnly);
    codeStream << code->toPlainText();
    codeFile.close();

    // Compile the program
    system((compilationMethod->currentData().toString() + " \"" + workingDirectory + codeFileName + "\" -o \""
            + workingDirectory + "program\"").toLocal8Bit().data());

    // Use the generated program to get the outputs
    for (int i(1); i <= testCasesList->count(); i++) {
        auto item = dynamic_cast<TestCase *>(testCasesList->itemAt(i - 1)->widget());
        // Write the input
        QFile inputFile(workingDirectory + "in/input" + QString::number(i) + ".txt");
        QTextStream inputText(&inputFile);
        inputFile.open(QIODevice::WriteOnly);
        inputText << item->getInput();
        inputFile.close();
        // Execute the program
        system(('\"' + workingDirectory + "program\" < \"" + workingDirectory + "in/input" + QString::number(i) + ".txt\" > \""
                + workingDirectory + "out/output" + QString::number(i) + ".txt\"").toLocal8Bit().data());
        // Read the output
        QFile outputFile(workingDirectory + "out/output" + QString::number(i) + ".txt");
        QTextStream outputStream(&outputFile);
        outputFile.open(QIODevice::ReadOnly);
        item->setOutput(outputStream.readAll());
        outputFile.close();
    }
}

MainWindow::MainWindow() : testCaseIndex(0) {
    initObjects();
    setupCodeSegment();
    setupOptions();
    setupTestCases();
    setupMainLayout();

    setFixedSize(720, 640);

    connect(addTestCase, &QPushButton::clicked, this, &MainWindow::newTestCase);
    connect(generateOutputs, &QPushButton::clicked, this, &MainWindow::generateFiles);
}
