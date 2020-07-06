#include "gui.h"
#include "Service.h"
#include "Repository.h"
#include <iostream>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::ifstream read("ConfigurationFile.txt");
    std::string repoType,myListLocation;
    getline(read,repoType);
    getline(read,myListLocation);
    Repository* repo;
    if(repoType.compare("inMemory") == 0)
        repo = new InMemoryRepository();
    else{
        repoType.erase(0,6);
        repo = new FileRepository(repoType.c_str());
    }
    Repository* watchList;
    if (myListLocation.find("html") != std::string::npos)
		watchList = new HTMLWatchList(myListLocation);
	else
        watchList = new CSVWatchList(myListLocation);
    Service* service = new Service(repo,watchList);
    FootageTableModel* model = new FootageTableModel(watchList);
    GUI gui(service,model);

    gui.show();
    return app.exec();
}
