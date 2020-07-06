#pragma once
#include "Domain.h"
#include "Repository.h"

class Action {
public:
	Action() {};
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() {};
};

class ActionAdd : public Action {
private:
	Footage addedFootage;
	Repository* repo;
public:
	ActionAdd(Footage& addedFootage, Repository* repo) : addedFootage{ addedFootage }, repo{ repo } { };
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdd() {};
};

class ActionRemove : public Action {
private:
	Footage deletedFootage;
	Repository* repo;
public:
	ActionRemove(Footage& deletedFootage, Repository* repo) : deletedFootage{ deletedFootage }, repo{ repo } { };
	void executeUndo() override;
	void executeRedo() override;
	~ActionRemove() {};
};

class ActionUpdate : public Action {
private:
	Footage initialFootage;
	Footage updatedFootage;
	Repository* repo;
public:
	ActionUpdate(Footage& initialFootage, Footage& updatedFootage, Repository* repo) : initialFootage{ initialFootage }, updatedFootage{ updatedFootage }, repo{ repo } { };
	void executeUndo() override;
	void executeRedo() override;
	~ActionUpdate() {};
};