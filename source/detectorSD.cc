#include "detectorSD.hh"

MySensitiveDetector::MySensitiveDetector(G4String name, const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name)
{
  G4cout << "MySensitiveDetector::MySensitiveDetector" << G4endl;
    
  fHitsCollection = nullptr;
  collectionName.insert(hitsCollectionName);
}

MySensitiveDetector::~MySensitiveDetector() {}

void MySensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
  G4cout << "MySensitiveDetector::Initialize" << G4endl;
  
  // Create hits collection
  fHitsCollection = new detectorHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4cout << "MySensitiveDetector::ProcessHits" << G4endl;
  
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit(); // [keV]
  
  auto newHit = new detectorHit();
  newHit->SetEdep(edep);

  if (fHitsCollection)
    fHitsCollection->insert( newHit );
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  G4cout << "MySensitiveDetector::EndOfEvent" << G4endl;
  
  G4int nofHits = fHitsCollection->entries();
  if ( verboseLevel>1 ) {
    G4cout << G4endl
    << "-------->Hits Collection: in this event they are " << nofHits
    << " hits in the SiPM detector: " << G4endl;
    for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }

  G4double totalEdep = 0.;
  for ( G4int i=0; i<nofHits; i++ )
  {
    totalEdep += (*fHitsCollection)[i]->GetEdep();
  }

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0, 0, totalEdep / keV); // [keV]
  man->AddNtupleRow(0);
}
