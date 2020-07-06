#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include "itoa.h"

class FootageTableModel : public QAbstractTableModel
{
    private:
        Repository* repo;
    public:
        FootageTableModel(Repository* repo) : repo{ repo } { }
        int rowCount(const QModelIndex& parent = QModelIndex()) const{
            return repo->getNumberOfRecordings();
        }
        int columnCount(const QModelIndex& parent = QModelIndex()) const{
            return 5;
        }
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const{
            int row = index.row();
            Footage footage = this->repo->getRecordings()[row];
            if(role == Qt::DisplayRole){
                switch(index.column()){
                    case 0:
                        return QString::fromStdString(footage.getTitle());
                    case 1:
                        return QString::fromStdString(footage.getLocation());
                    case 2:
                    {   
                        struct tm time = footage.getTimeOfCreation();
                        char timeOfCreation[12];
                        char partOfTime[5];
                        sprintf(partOfTime,"%d",time.tm_mon);
    //                    itoa(time.tm_mon, partOfTime, 10);
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
                        return QString(timeOfCreation);
                    }
                    case 3:
                        return QString::number(footage.getTimesAccesed());
                    case 4:
                        return QString::fromStdString(footage.getFootagePreview());
                    default:
                        break;
                }
            }

            return QVariant();
        }

        QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole) const{
            if(role == Qt::DisplayRole){
                if (orientation == Qt::Horizontal){
                    switch(section){
                        case 0:
                            return QString("Title");
                        case 1:
                            return QString("Location");
                        case 2:
                            return QString("Time of creation");
                        case 3:
                            return QString("Times accesed");
                        case 4:
                            return QString("Footage preview");
                    }
                }
                else if(orientation == Qt::Vertical){
                    return QString::number(section+1);
                }
            }
            return QVariant();
        }

        void reset(){
            this->beginResetModel();
            this->endResetModel();
        }
};