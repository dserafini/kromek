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

  // step 
  newHit->SetPosition(aStep->GetPreStepPoint()->GetPosition());
  
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
  G4double partEdep = 0.;
  G4ThreeVector totalStep = G4ThreeVector();
  for ( G4int i=0; i<nofHits; i++ )
  {
    partEdep = (*fHitsCollection)[i]->GetEdep();
    totalEdep += partEdep;
    totalStep += (*fHitsCollection)[i]->GetPosition() * partEdep;
  }
  
  // normalize fPosition on total energy deposit
  if (totalEdep > 0)
    fPosition /= totalEdep;

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(Tuples::kDetector, TDetector::kEdep, totalEdep / keV); // [keV]
  man->FillNtupleDColumn(Tuples::kDetector, TDetector::kGammaX, fPosition.getX() / mm); // [mm]
  man->FillNtupleDColumn(Tuples::kDetector, TDetector::kGammaY, fPosition.getY() / mm);
  man->FillNtupleDColumn(Tuples::kDetector, TDetector::kGammaZ, fPosition.getZ() / mm);
  man->AddNtupleRow(Tuples::kDetector);
}
