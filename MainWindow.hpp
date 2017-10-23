#ifndef QTC_GENERATOR_MAIN_WINDOW_HPP
#define QTC_GENERATOR_MAIN_WINDOW_HPP

#include <unistd.h>
#include <QDir>
#include <QLabel>
#include <QFrame>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QTextStream>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPlainTextEdit>
#include "TestCase.hpp"
#include "DraggableButton.hpp"

class MainWindow : public QWidget {
    Q_OBJECT
    int testCaseIndex;
    QVBoxLayout *mainLayout, *codeSegmentLayout, *testCasesLayout, *testCasesList;
    QGroupBox *codeSegment, *options, *testCases;
    QHBoxLayout *optionsLayout;
    QScrollArea *testCasesScroll;
    QFrame *testCasesFrame;
    QComboBox *compilationMethod;
    QPushButton *addTestCase, *generateOutputs;
    DraggableButton *dragZipArchive;
    QPlainTextEdit *code;
    void initObjects();
    void setupMainLayout();
    void setupCodeSegment();
    void setupOptions();
    void setupTestCases();
public slots:
    void newTestCase();
    void removeTestCase(int index);
    void generateFiles();
public:
    MainWindow();
};

#endif
