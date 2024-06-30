#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4cout << "MyPrimaryGenerator::MyPrimaryGenerator" << G4endl;
	fParticleGun = new G4ParticleGun();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
