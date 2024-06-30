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

	// aluminium
	G4Material* materialAl = new G4Material("Al", 2.699 * g/cm3, 1);
	materialAl->AddElement(nist->FindOrBuildElement("Al"), 1);

	// czt case
	materialCztCase = (G4Material*) materialAl;

	// czt crystal
	materialCztCrystal = new G4Material("czt",  5.605 * g/cm3, 3);
	materialCztCrystal->AddElement(nist->FindOrBuildElement("Cd"), 1);
	materialCztCrystal->AddElement(nist->FindOrBuildElement("Zn"), 1);
	materialCztCrystal->AddElement(nist->FindOrBuildElement("Te"), 1);
}

void MyDetectorConstruction::ConstructCzt()
{
	// kromek czt case
	G4double cztCaseHalfXY = .7 * cm;
	G4double cztCaseHalfZ = 3 * cm;
	G4double cztWindowDistance = 9 * cm;
	G4ThreeVector cztCasePosition = G4ThreeVector(0, 0, cztWindowDistance + cztCaseHalfZ);
	solidCztCase = new G4Box('solidCztCase', cztCaseHalfXY, cztCaseHalfXY, cztCaseHalfZ);
	logicCztCase = new G4LogicalVolume(solidCztCase, materialCztCase, 'logicCztCase', 0, 0, 0, true);
	new G4PVPlacement(0, cztCasePosition, logicCztCase, "physCztCrystal", logicWorld, false, 0, true);

	// czt crystal
	G4double cztCrystalHalfXYZ = .5 * cm;
	G4ThreeVector cztCrystalPosition = G4ThreeVector(0, 0, -1 * cm);
	solidCztCrystal = new G4Box('solidCztCrystal', cztCrystalHalfXYZ, cztCrystalHalfXYZ, cztCrystalHalfXYZ);
	logicCztCrystal = new G4LogicalVolume(solidCztCrystal, materialCztCrystal, 'logicCztCrystal', 0, 0, 0, true);
	new G4PVPlacement(0, cztCrystalPosition, logicCztCrystal, "physCztCrystal", logicCztCase, false, 0, true);
}

void MyDetectorConstruction::ConstructFlange()
{
	// flange
	G4double flangeDistance = 5.4 * cm;
	G4ThreeVector flangePosition = G4ThreeVector(0, 0, flangeDistance);
	solidFlange = new G4Tubs('solidFlange', 0 * cm, 6.5 * cm, .55 * cm, 0 * deg, 360 * deg);
	logicFlange = new G4LogicalVolume(solidFlange, materialFlange, 'logicFlange', 0, 0, 0, true);
	new G4PVPlacement(0, flangePosition, logicFlange, 'physFlange', logicWorld, false, 0, true);
}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
	G4cout << "MyDetectorConstruction::Construct" << G4endl;
	
	DefineMaterials();

	// world
	G4double world_half_Z  = 10*cm;
	G4double world_half_XY = 10*cm;
	G4Box* solidWorld = new G4Box("solidWorld", world_half_XY, world_half_XY, world_half_Z);
	logicWorld = new G4LogicalVolume(solidWorld, materialAir, "logicWorld", 0, 0, 0, true);
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);
	
	ConstructCzt();
	
	return physWorld;
}



void MyDetectorConstruction::ConstructSDandField()
{
	G4cout << "MyDetectorConstruction::ConstructSDandField" << G4endl;
}
