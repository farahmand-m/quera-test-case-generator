#ifndef QTC_GENERATOR_TEST_CASE_HPP
#define QTC_GENERATOR_TEST_CASE_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

class TestCase : public QWidget {
    Q_OBJECT
    QHBoxLayout *layout;
    QPushButton *remove;
    QPlainTextEdit *input, *output;
    void initObjects();
    void setupLayout();
signals:
    void isRemoved(int index);
public slots:
    void removed();
public:
    const int index;
    explicit TestCase(int index);
    QString getInput();
    void setOutput(QString plainText);
};

#endif
