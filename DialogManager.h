#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

namespace DialogManager {

    class CategoryDialog : public QDialog {
    public:
        CategoryDialog(const QString& currentName = "", QWidget* parent = nullptr);
        QString getName() const;

    private:
        QLineEdit* nameEdit;
    };

    class ButtonDialog : public QDialog {
    public:
        ButtonDialog(const QString& currentName = "", const QString& currentCommand = "", QWidget* parent = nullptr);
        QString getName() const;
        QString getCommand() const;

    private:
        QLineEdit* nameEdit;
        QLineEdit* commandEdit;
    };

} // namespace DialogManager

#endif // DIALOGMANAGER_H