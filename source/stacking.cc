#include "stacking.hh"

MyStackingAction::MyStackingAction()
{
	G4cout << "MyStackingAction::MyStackingAction" << G4endl;
}

MyStackingAction::~MyStackingAction() {}

G4ClassificationOfNewTrack MyStackingAction::ClassifyNewTrack(
	const G4Track* aTrack)
{
	// kill all neutrinos
	if(aTrack->GetDefinition() == G4NeutrinoE::Definition())
		return fKill;
	// kill all anti-neutrinos
	if(aTrack->GetDefinition() == G4AntiNeutrinoE::Definition())
		return fKill;
	
	return fUrgent;
}
