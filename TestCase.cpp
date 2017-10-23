#include "TestCase.hpp"

void TestCase::initObjects() {
    layout = new QHBoxLayout(this);
    input  = new QPlainTextEdit;
    output = new QPlainTextEdit;
    remove = new QPushButton("Remove");
}

void TestCase::setupLayout() {
    QFont ubuntuMono("Ubuntu Mono");

    input->setFont(ubuntuMono);
    input->setPlaceholderText("Input");
    input->setWordWrapMode(QTextOption::NoWrap);

    output->setFont(ubuntuMono);
    output->setPlaceholderText("Output");
    output->setWordWrapMode(QTextOption::NoWrap);

    layout->addWidget(input);
    layout->addWidget(output);
    layout->addWidget(remove);
}

void TestCase::removed() {
    emit isRemoved(index);
}

TestCase::TestCase(int index) : index(index) {
    initObjects();
    setupLayout();

    setMinimumHeight(sizeHint().height() * .5);

    connect(remove, &QPushButton::clicked, this, &TestCase::removed);
}

QString TestCase::getInput() {
    return input->toPlainText();
}

void TestCase::setOutput(QString plainText) {
    output->setPlainText(plainText);
}