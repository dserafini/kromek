#include "construction.hh"

G4double HalfVoxelSize;
G4double HalfPhantomDepth;
G4double mouseCollimatorDistance;

MyDetectorConstruction::MyDetectorConstruction()
{
	G4cout << "MyDetectorConstruction::MyDetectorConstruction" << G4endl;
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

// to define material only once
void MyDetectorConstruction::DefineMaterials()
{
	G4cout << "MyDetectorConstruction::DefineMaterials" << G4endl;
	G4NistManager *nist = G4NistManager::Instance();

	G4Material* materialAir      = nist->FindOrBuildMaterial("G4_AIR");
}


G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
	G4cout << "MyDetectorConstruction::Construct" << G4endl;
	G4double world_half_Z  = 10*cm;
	G4double world_half_XY = 10*cm;

	solidWorld = new G4Box("solidWorld", world_half_XY, world_half_XY, world_half_Z);
	logicWorld = new G4LogicalVolume(solidWorld, materialAir, "logicWorld", 0, 0, 0, true);

	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);

	return physWorld;
}



void MyDetectorConstruction::ConstructSDandField()
{
	G4cout << "MyDetectorConstruction::ConstructSDandField" << G4endl;
}
