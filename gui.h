#ifndef GUI_H
#define GUI_H
#pragma once
#include <QList>
#include <QModelIndexList>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QMessageBox>
#include "Service.h"
#include <string>
#include <set>
#include "tableofsavedrecordings.h"
#include "FootageModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI;}
QT_END_NAMESPACE

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service* service,QAbstractItemModel* model, QWidget *parent = nullptr);
    ~GUI();
    void connectSignalsAndSlots();
private:
    Service* service;
    Ui::GUI *ui;
    QAbstractItemModel* model;
    TableOfSavedRecordings *tableView;
};

#endif // GUI_H
