#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	G4cout << "MyDetectorConstruction::MyDetectorConstruction" << G4endl;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

// to define material only once
void MyDetectorConstruction::DefineMaterials()
{
	G4cout << "MyDetectorConstruction::DefineMaterials" << G4endl;
	G4NistManager *nist = G4NistManager::Instance();

	materialAir = nist->FindOrBuildMaterial("G4_AIR");
}

void MyDetectorConstruction::ConstructCzt()
{
	// kromek czt case
	G4double cztCaseHalfXY = .7 * cm;
	G4double cztCaseHalfZ = 3 * cm;
	G4Box *solidCztCase = new G4Box('solidCztCase', cztCaseHalfXY, cztCaseHalfXY, cztCaseHalfZ);
	G4LogicalVolume *logicCztCase = new G4LogicalVolume(solidCztCase, materialAir, 'logicCztCase', 0, 0, 0, true);
	new G4PVPlacement(0, G4ThreeVector(), logicCztCase, "physCztCrystal", logicWorld, false, 0, true);

	// czt crystal
	G4double cztCrystalHalfXYZ = .5 * cm;
	G4Box *solidCztCrystal = new G4Box('solidCztCrystal', cztCrystalHalfXYZ, cztCrystalHalfXYZ, cztCrystalHalfXYZ);
	G4LogicalVolume *logicCztCrystal = new G4LogicalVolume(solidCztCrystal, materialAir, 'logicCztCrystal', 0, 0, 0, true);
	new G4PVPlacement(0, G4ThreeVector(), logicCztCrystal, "physCztCrystal", logicCztCase, false, 0, true);
}


G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
	G4cout << "MyDetectorConstruction::Construct" << G4endl;
	DefineMaterials();
	G4double world_half_Z  = 10*cm;
	G4double world_half_XY = 10*cm;

	if (materialAir)
	{
		G4cout << "c'è aria" << G4endl;
		G4Box* solidWorld = new G4Box("solidWorld", world_half_XY, world_half_XY, world_half_Z);
		logicWorld = new G4LogicalVolume(solidWorld, materialAir, "logicWorld", 0, 0, 0, true);
		physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);
	}
	else
		G4cout << "non c'è aria" << G4endl;
	
	ConstructCzt();
	
	return physWorld;
}



void MyDetectorConstruction::ConstructSDandField()
{
	G4cout << "MyDetectorConstruction::ConstructSDandField" << G4endl;
}
