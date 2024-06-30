#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4cout << "MyPrimaryGenerator::MyPrimaryGenerator" << G4endl;
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{}
