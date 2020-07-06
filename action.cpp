#include "action.h"

void ActionAdd::executeUndo() {
	this->repo->deleteFootage(this->addedFootage);
}

void ActionAdd::executeRedo() {
	this->repo->addFootage(this->addedFootage);
}

void ActionRemove::executeUndo() {
	this->repo->addFootage(this->deletedFootage);
}

void ActionRemove::executeRedo() {
	this->repo->deleteFootage(this->deletedFootage);
}

void ActionUpdate::executeUndo() {
	this->repo->updateFootage(this->initialFootage);
}

void ActionUpdate::executeRedo() {
	this->repo->updateFootage(this->updatedFootage);
}