#include "stacking.hh"

MyStackingAction::MyStackingAction()
{
	G4cout << "MyStackingAction::MyStackingAction" << G4endl;
}

MyStackingAction::~MyStackingAction() {}

G4ClassificationOfNewTrack MyStackingAction::ClassifyNewTrack(
	const G4Track* aTrack)
{
	// kill every particle that is not a gamma-ray
	if(aTrack->GetDefinition() != G4Gamma::Definition())
		return fKill;
	
	return fUrgent;
}
