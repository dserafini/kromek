// trick to not include multiple times
#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "detectorSD.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	// need contructor and destructor
	MyDetectorConstruction();
	~MyDetectorConstruction();

	virtual G4VPhysicalVolume *Construct();
	// virtual because it is defined in G4USerDetectorConstruction

private:
	virtual void ConstructSDandField();
	void DefineMaterials();

	// world
	G4LogicalVolume* logicWorld;
	G4VPhysicalVolume* physWorld;
	G4Material* materialAir;

	// czt
	void ConstructCzt();
	//case
	G4Box *solidCztCase;
	G4LogicalVolume *logicCztCase;
	G4Material* materialCztCase;
	// crystal
	G4Box *solidCztCrystal;
	G4LogicalVolume *logicCztCrystal;
	G4Material* materialCztCrystal;

	// flange
	void ConstructFlange();
	G4Tubs *solidFlange;
	G4LogicalVolume *logicFlange;
	G4Material *materialFlange;

	// source
	void ConstructSource();
	G4Orb *solidSource;
	G4LogicalVolume *logicSource;
	G4Material *materialSource;
};

#endif
