#ifndef DETECTORSD_HH
#define DETECTORSD_HH

#include "G4VSensitiveDetector.hh"
#include "g4root.hh" // ok with geant version 10.7
// #include "g4root_defs.hh" // ok with geant version 11.1
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "detectorHit.hh"
#include "enums.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
	MySensitiveDetector(G4String, const G4String&);
	~MySensitiveDetector();
	void Initialize(G4HCofThisEvent* hitCollection) override;
	void SetEdep(G4double de) { fEdep = de; };
	void SetPosition(G4ThreeVector tp) { fPosition = tp; };
	G4double GetEdep() const { return fEdep; };
	G4ThreeVector GetPosition() const { return fPosition; };

private:
	G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
	void EndOfEvent(G4HCofThisEvent* hitCollection) override;
	
	detectorHitsCollection* fHitsCollection;
	G4double      fEdep = 0.;
	G4ThreeVector      fPosition = G4ThreeVector();
};

#endif
