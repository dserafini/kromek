#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4cout << "MyPrimaryGenerator::MyPrimaryGenerator" << G4endl;
	fParticleGun = new G4ParticleGun();
	fParticleGps = new G4GeneralParticleSource();

	// default particle kinematic
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	fParticleGun->SetParticleEnergy(0. * eV);

	// default particle kinematic
	fParticleGps->SetParticleDefinition(particle);
	fParticleGps->GetCurrentSource()->GetEneDist()->SetMonoEnergy(1.0 * MeV);
	fParticleGps->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.0, 0.0, 0.0));
    fParticleGps->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
	delete fParticleGps;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
	
	if(particle == G4Geantino::Geantino())
	{
		G4int Z = 63; // Eu
		G4int A = 152;
		
		G4double charge = 0. * eplus;
		G4double energy = 0. * keV;
		
		G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}

	fParticleGps->GeneratePrimaryVertex(anEvent);
}
