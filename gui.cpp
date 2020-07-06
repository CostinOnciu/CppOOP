#pragma once
#include "gui.h"
#include "ui_gui.h"
#include <stdio.h>
#include <QShortcut>
using namespace std;

GUI::GUI(Service* service, QAbstractItemModel* model, QWidget *parent)
    :service{service}, QWidget(parent), model(model),
    ui(new Ui::GUI), tableView(new TableOfSavedRecordings(model))
{
    ui->setupUi(this);
    this->connectSignalsAndSlots();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::connectSignalsAndSlots()
    {
        QObject::connect(ui->ViewButton,&QPushButton::clicked,[this](){this->tableView->show();});
        QObject::connect(ui->FilterButton,&QPushButton::clicked,[this](){
            auto locationFilter = ui->FilterLocationEdit->text().toStdString();
            auto timesAccesedFilter = ui->FilterTimesAccesedEdit->text().toStdString();

            if(locationFilter == "" || timesAccesedFilter == ""){
                QMessageBox::critical(this,"error","Invalid filter options");
                return;
            }
            int timesAccesed;
            try{
                timesAccesed = stoi(timesAccesedFilter);
            }
            catch(...){
                QMessageBox::critical(this,"error","Invalid filter options");
                return;
            }
            ui->TableOfRecordingsToSave->clearContents();
            int index = 0;
            auto recordings1 = this->service->getRecordings();
            ui->TableOfRecordingsToSave->setRowCount(recordings1.size());
            for(auto recording:recordings1){
                if(recording.getLocation() == locationFilter && recording.getTimesAccesed() <= timesAccesed){
                auto recordingTitleSecond = new QTableWidgetItem(recording.getTitle().c_str());
                auto recordingLocationSecond = new QTableWidgetItem(recording.getLocation().c_str());
                        
                struct tm time = recording.getTimeOfCreation();
                char timeOfCreation[12];
                char partOfTime[5];
                sprintf(partOfTime,"%d",time.tm_mon);
                //qDebug()<<partOfTime;
	//itoa(time.tm_mon, partOfTime, 10);
                if (time.tm_mon < 10) {
                    strcpy(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);
                }
                else
                    strcpy(timeOfCreation, partOfTime);

                strcat(timeOfCreation, "-");

                sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                //qDebug()<<partOfTime << time.tm_mon);
                if (time.tm_mday < 10)
                    strcat(timeOfCreation, "0");
                strcat(timeOfCreation, partOfTime);

                strcat(timeOfCreation, "-");

                sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                //qDebug()<<partOfTime;
                strcat(timeOfCreation, partOfTime);

                auto recordingTimeOfCreationSecond = new QTableWidgetItem(timeOfCreation);
                auto recordingTimesAccessedSecond = new QTableWidgetItem(std::to_string(recording.getTimesAccesed()).c_str());
                auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                ui->TableOfRecordingsToSave->setItem(index,0,recordingTitleSecond);
                ui->TableOfRecordingsToSave->setItem(index,1,recordingLocationSecond);
                ui->TableOfRecordingsToSave->setItem(index,2,recordingTimeOfCreationSecond);
                ui->TableOfRecordingsToSave->setItem(index,3,recordingTimesAccessedSecond);
                ui->TableOfRecordingsToSave->setItem(index,4,recordingFootagePreviewSecond);
                        
                index++;
                }
            }
        });

        QObject::connect(ui->OpenButton,&QPushButton::clicked,[this](){
            service->open();
        });

        QObject::connect(ui->AddButton,&QPushButton::clicked,ui->TableOfRecordings,[this](){ui->TableOfRecordings->setRowCount(ui->TableOfRecordings->rowCount()+1);});
        
        auto  recordings = this->service->getRecordings();
        ui->TableOfRecordings->setRowCount(recordings.size());
        ui->TableOfRecordingsToSave->setRowCount(recordings.size());
        //QLabel* debug = new QLabel{QString::fromStdString(recordings[0].getTitle())};
        //verticalLayout->addWidget(debug);
        ui->TableOfRecordings->clearContents();
        ui->TableOfRecordingsToSave->clearContents();

        int index = 0;
        for(auto recording:recordings){
            auto recordingTitleFirst = new QTableWidgetItem{recording.getTitle().c_str()};
            auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};
            
            auto recordingLocationFirst = new QTableWidgetItem{recording.getLocation().c_str()};
            auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
            
            struct tm time = recording.getTimeOfCreation();
            char timeOfCreation[12];
            char partOfTime[5];
            sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
            if (time.tm_mon < 10) {
                strcpy(timeOfCreation, "0");
                strcat(timeOfCreation, partOfTime);
            }
            else
                strcpy(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
            if (time.tm_mday < 10)
                strcat(timeOfCreation, "0");
            strcat(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
            strcat(timeOfCreation, partOfTime);

            auto recordingTimeOfCreationFirst = new QTableWidgetItem{timeOfCreation};
            auto recordingTimesAccessedFirst = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
            auto recordingFootagePreviewFirst = new QTableWidgetItem(recording.getFootagePreview().c_str());
            
            auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
            auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
            auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

            ui->TableOfRecordings->setItem(index,0,recordingTitleFirst);
            ui->TableOfRecordings->setItem(index,1,recordingLocationFirst);
            ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationFirst);
            ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedFirst);
            ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewFirst);


            ui->TableOfRecordingsToSave->setItem(index,0,recordingTitleSecond);
            ui->TableOfRecordingsToSave->setItem(index,1,recordingLocationSecond);
            ui->TableOfRecordingsToSave->setItem(index,2,recordingTimeOfCreationSecond);
            ui->TableOfRecordingsToSave->setItem(index,3,recordingTimesAccessedSecond);
            ui->TableOfRecordingsToSave->setItem(index,4,recordingFootagePreviewSecond);
            
            index++;
        } 
        QObject::connect(ui->NextButton,&QPushButton::clicked,[this](){
            Footage currentFootage;
            try{
                currentFootage = this->service->next();
            }
            catch(exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            ui->TitleEdit->setText(currentFootage.getTitle().c_str());
            ui->LocationEdit->setText(currentFootage.getLocation().c_str());
            struct tm time = currentFootage.getTimeOfCreation();
            char timeOfCreation[12];
            char partOfTime[5];
            sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
            if (time.tm_mon < 10) {
                strcpy(timeOfCreation, "0");
                strcat(timeOfCreation, partOfTime);
            }
            else
                strcpy(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
            if (time.tm_mday < 10)
                strcat(timeOfCreation, "0");
            strcat(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
            strcat(timeOfCreation, partOfTime);
    
            ui->TimeOfCreationEdit->setText(timeOfCreation);
            ui->TimesAccesedEdit->setText(to_string(currentFootage.getTimesAccesed()).c_str());
            ui->FootagePreviewEdit->setText(currentFootage.getFootagePreview().c_str());
        });
        QObject::connect(ui->SaveButton,&QPushButton::clicked,[this](){
            try{
                this->service->addRecording(ui->TitleEdit->text().toStdString());  
                dynamic_cast<FootageTableModel*>(model)->reset();
            }
            catch(exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            auto footages = this->service->getWatchList();
            ui->ListOfSavedRecordings->clear();
            //qDebug() << footages.size();
            for(auto footage:footages){
                std::string item = footage.getTitle();
                item += " ";
                item += footage.getLocation();
                item += " ";
                struct tm time = footage.getTimeOfCreation();
                char timeOfCreation[12];
                char partOfTime[5];
                sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                if (time.tm_mon < 10) {
                    strcpy(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);
                }
                else
                    strcpy(timeOfCreation, partOfTime);

                strcat(timeOfCreation, "-");

                sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                if (time.tm_mday < 10)
                    strcat(timeOfCreation, "0");
                strcat(timeOfCreation, partOfTime);

                strcat(timeOfCreation, "-");

                sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                strcat(timeOfCreation, partOfTime);
                item += timeOfCreation;
                
                int timesAccesed = footage.getTimesAccesed();
                item += " ";
                item += to_string(timesAccesed);
                item += " ";
                item += footage.getFootagePreview();
                
                QListWidgetItem* Item = new QListWidgetItem{item.c_str()};
                ui->ListOfSavedRecordings->addItem(Item);
                //qDebug() << item.c_str();
            }
            //qDebug() << "added";
        });
        QObject::connect(ui->DeleteButton,&QPushButton::clicked,[this](){
            std::set<int> rows;
            QModelIndexList indexes = ui->TableOfRecordings->selectionModel()->selection().indexes();
            for (int i = 0; i < indexes.count(); ++i)
            {
	            QModelIndex index = indexes.at(i);
                int row = index.row();
                rows.insert(row);
            }

            auto recordings1 = this->service->getRecordings();

            for(auto row:rows)
                this->service->deleteFootage(recordings1[row].getTitle());
            recordings1 = this->service->getRecordings();
        
            ui->TableOfRecordingsToSave->clearContents();
            int index = 0;
            ui->TableOfRecordingsToSave->setRowCount(recordings1.size());
            ui->TableOfRecordings->clearContents();
            ui->TableOfRecordings->setRowCount(recordings1.size());
            for(auto recording:recordings1){
            auto recordingTitleFirst = new QTableWidgetItem{recording.getTitle().c_str()};
            auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};
            
            auto recordingLocationFirst = new QTableWidgetItem{recording.getLocation().c_str()};
            auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
            
            struct tm time = recording.getTimeOfCreation();
            char timeOfCreation[12];
            char partOfTime[5];
            sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
            if (time.tm_mon < 10) {
                strcpy(timeOfCreation, "0");
                strcat(timeOfCreation, partOfTime);
            }
            else
                strcpy(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
            if (time.tm_mday < 10)
                strcat(timeOfCreation, "0");
            strcat(timeOfCreation, partOfTime);

            strcat(timeOfCreation, "-");

            sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
            strcat(timeOfCreation, partOfTime);

            auto recordingTimeOfCreationFirst = new QTableWidgetItem{timeOfCreation};
            auto recordingTimesAccessedFirst = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
            auto recordingFootagePreviewFirst = new QTableWidgetItem(recording.getFootagePreview().c_str());
            
            auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
            auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
            auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

            ui->TableOfRecordings->setItem(index,0,recordingTitleFirst);
            ui->TableOfRecordings->setItem(index,1,recordingLocationFirst);
            ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationFirst);
            ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedFirst);
            ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewFirst);


            ui->TableOfRecordingsToSave->setItem(index,0,recordingTitleSecond);
            ui->TableOfRecordingsToSave->setItem(index,1,recordingLocationSecond);
            ui->TableOfRecordingsToSave->setItem(index,2,recordingTimeOfCreationSecond);
            ui->TableOfRecordingsToSave->setItem(index,3,recordingTimesAccessedSecond);
            ui->TableOfRecordingsToSave->setItem(index,4,recordingFootagePreviewSecond);
            
            index++;
        } 
        });
        QObject::connect(ui->TableOfRecordings,&QTableWidget::itemChanged,[this](){
            ui->TableOfRecordings->blockSignals(true);
            int row = ui->TableOfRecordings->currentRow();
            auto recordings1 = this->service->getRecordings();
            try{
            if(row < recordings1.size()){
                //qDebug() << "to update";
                std::string title = ui->TableOfRecordings->item(row,0)->text().toStdString();
                std::string location = ui->TableOfRecordings->item(row,1)->text().toStdString();
                std::string timeOfCreation = ui->TableOfRecordings->item(row,2)->text().toStdString();
                int timesAccesed = ui->TableOfRecordings->item(row,3)->text().toInt();
                std::string footagePreview = ui->TableOfRecordings->item(row,4)->text().toStdString();
                this->service->updateFootage(title,location,timeOfCreation,timesAccesed,footagePreview);
                
                ui->TableOfRecordingsToSave->clearContents();
                int index = 0;
                recordings1 = this->service->getRecordings();
                ui->TableOfRecordingsToSave->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordingsToSave->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordingsToSave->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordingsToSave->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordingsToSave->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordingsToSave->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
            }
            else{
                int column = ui->TableOfRecordings->currentColumn();
                if(column == 4){
                    std::string title = ui->TableOfRecordings->item(row,0)->text().toStdString();
                    std::string location = ui->TableOfRecordings->item(row,1)->text().toStdString();
                    std::string timeOfCreation = ui->TableOfRecordings->item(row,2)->text().toStdString();
                    int timesAccesed = ui->TableOfRecordings->item(row,3)->text().toInt();
                    std::string footagePreview = ui->TableOfRecordings->item(row,4)->text().toStdString();
                    this->service->addFootage(title,location,timeOfCreation,timesAccesed,footagePreview);

                    ui->TableOfRecordingsToSave->clearContents();
                    int index = 0;
                    recordings1 = this->service->getRecordings();
                    ui->TableOfRecordingsToSave->setRowCount(recordings1.size());
                    for(auto recording:recordings1){
                        auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};
                        auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                        
                        struct tm time = recording.getTimeOfCreation();
                        char timeOfCreation[12];
                        char partOfTime[5];
                        sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                        if (time.tm_mon < 10) {
                            strcpy(timeOfCreation, "0");
                            strcat(timeOfCreation, partOfTime);
                        }
                        else
                            strcpy(timeOfCreation, partOfTime);

                        strcat(timeOfCreation, "-");

                        sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                        if (time.tm_mday < 10)
                            strcat(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);

                        strcat(timeOfCreation, "-");

                        sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                        strcat(timeOfCreation, partOfTime);

                        auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                        auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                        auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                        ui->TableOfRecordingsToSave->setItem(index,0,recordingTitleSecond);
                        ui->TableOfRecordingsToSave->setItem(index,1,recordingLocationSecond);
                        ui->TableOfRecordingsToSave->setItem(index,2,recordingTimeOfCreationSecond);
                        ui->TableOfRecordingsToSave->setItem(index,3,recordingTimesAccessedSecond);
                        ui->TableOfRecordingsToSave->setItem(index,4,recordingFootagePreviewSecond);
                        
                        index++;
                    }
                }
            }
            }
            catch(std::exception& error){
                QMessageBox::critical(this,"error",error.what());
                auto recordings1 = this->service->getRecordings();
                ui->TableOfRecordings->clearContents();
                int index = 0;
                ui->TableOfRecordings->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};                        
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);
                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordings->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordings->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
            }
            ui->TableOfRecordings->blockSignals(false);
            
        });

        QObject::connect(this->ui->UndoButton,&QPushButton::clicked,[this](){
            try{
            this->service->undo();
            }
            catch(std::exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            auto recordings1 = this->service->getRecordings();
                ui->TableOfRecordings->clearContents();
                int index = 0;
                ui->TableOfRecordings->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};                        
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);
                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordings->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordings->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
        });

        QObject::connect(this->ui->RedoButton,&QPushButton::clicked,[this](){
            try{
            this->service->redo();
            }
            catch(std::exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            auto recordings1 = this->service->getRecordings();
                ui->TableOfRecordings->clearContents();
                int index = 0;
                ui->TableOfRecordings->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};                        
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);
                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordings->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordings->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
        });
        QShortcut *shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"),this);
        QShortcut *shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"),this);

        QObject::connect(shortcutUndo, &QShortcut::activated, [this](){
            try{
            this->service->undo();
            }
            catch(std::exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            auto recordings1 = this->service->getRecordings();
                ui->TableOfRecordings->clearContents();
                int index = 0;
                ui->TableOfRecordings->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};                        
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);
                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordings->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordings->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
        });

        QObject::connect(shortcutRedo, &QShortcut::activated, [this](){
            try{
            this->service->redo();
            }
            catch(std::exception& error){
                QMessageBox::critical(this,"error",error.what());
                return;
            }
            auto recordings1 = this->service->getRecordings();
                ui->TableOfRecordings->clearContents();
                int index = 0;
                ui->TableOfRecordings->setRowCount(recordings1.size());
                for(auto recording:recordings1){
                    auto recordingTitleSecond = new QTableWidgetItem{recording.getTitle().c_str()};                        
                    auto recordingLocationSecond = new QTableWidgetItem{recording.getLocation().c_str()};
                    
                    struct tm time = recording.getTimeOfCreation();
                    char timeOfCreation[12];
                    char partOfTime[5];
                    sprintf(partOfTime,"%d",time.tm_mon);
	//itoa(time.tm_mon, partOfTime, 10);
                    if (time.tm_mon < 10) {
                        strcpy(timeOfCreation, "0");
                        strcat(timeOfCreation, partOfTime);
                    }
                    else
                        strcpy(timeOfCreation, partOfTime);
                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
                    if (time.tm_mday < 10)
                        strcat(timeOfCreation, "0");
                    strcat(timeOfCreation, partOfTime);

                    strcat(timeOfCreation, "-");

                    sprintf(partOfTime,"%d",time.tm_year);
	//itoa(time.tm_year, partOfTime, 10);
                    strcat(timeOfCreation, partOfTime);

                    auto recordingTimeOfCreationSecond = new QTableWidgetItem{timeOfCreation};
                    auto recordingTimesAccessedSecond = new QTableWidgetItem{std::to_string(recording.getTimesAccesed()).c_str()};
                    auto recordingFootagePreviewSecond = new QTableWidgetItem(recording.getFootagePreview().c_str());

                    ui->TableOfRecordings->setItem(index,0,recordingTitleSecond);
                    ui->TableOfRecordings->setItem(index,1,recordingLocationSecond);
                    ui->TableOfRecordings->setItem(index,2,recordingTimeOfCreationSecond);
                    ui->TableOfRecordings->setItem(index,3,recordingTimesAccessedSecond);
                    ui->TableOfRecordings->setItem(index,4,recordingFootagePreviewSecond);
                    
                    index++;
                }
        });

        //QObject::connect(ui->actionUndo,&QAction::triggered,
    }