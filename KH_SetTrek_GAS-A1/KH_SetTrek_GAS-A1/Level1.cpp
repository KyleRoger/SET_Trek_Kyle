#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"
#include "Mouse.h"


void Level1::Load()
{
	gameStart = true;
	windowWidth = gfx->GetWindowWidth();
	windowHeight = gfx->GetWindowHeight();
	gridWidth = windowWidth / 10;
	gridHeight = windowHeight / 10;

	//Create the objects with the images gicen in the assignement
	background = new SpriteSheet(L"Images\\SectorBackground.bmp", gfx); //This is where we can specify our file system object!
	planet1 = new SpriteSheet(L"Images\\Planet1.bmp", gfx);
	planet2 = new SpriteSheet(L"Images\\Planet2.bmp", gfx);
	planet3 = new SpriteSheet(L"Images\\Planet3.bmp", gfx);
	miniGameLayout = new SpriteSheet(L"Images\\miniGameLayout.bmp", gfx);
	shipDetails = new Starship(gfx);
	shipBase = new Starship(gfx);
	enemyShip = new Starship(gfx);
	shipDetails->InitImage(L"Images\\ShipDetail.bmp");
	shipBase->InitImage(L"Images\\ShipBase.bmp");
	enemyShip->InitImage(L"Images\\EnemyShip.bmp");



	//Chroma Key the planets
	planet1->ApplyChromaEffect();
	planet2->ApplyChromaEffect();
	planet3->ApplyChromaEffect();

	//Apply the Chroma Key to the shipBase and shipDetails.
	shipBase->ShipChromaKey(0.0f, 1.0f, 0.0f);
	shipDetails->ShipChromaKey(0.0f, 1.0f, 0.0f);

	shipBase->SetXCoordinate(0.0);
	shipDetails->SetXCoordinate(0.0);
	shipBase->SetYCoordinate(windowHeight / 2);
	shipDetails->SetYCoordinate(windowHeight / 2);

	enemyShip->SetXCoordinate(windowWidth - gridWidth);
	enemyShip->SetYCoordinate(windowHeight / 2);

	enemyShip->ShipChromaKey(0.0f, 0.0f, 1.0f);

	//Move the player forward
	//moving->PlayerMove();

	//Create a grid, construct it, create random coordinates and randomize the planets.
	newGrid = new Grid(windowWidth, windowHeight);
	newGrid->ConstructGrid();
	newGrid->CreateRandomCoordinates();
	newGrid->PlanetRandomize(planet1, planet2, planet3);


}


void Level1::Unload()
{
	delete background;
	delete planet1;
	delete planet2;
	delete planet3;
	delete shipBase;
	delete shipDetails;
	delete enemyShip;
}

//Name: Update
//Purpose: The purpose of this method is to update the game state. This is repeatedly
//			called within the fame loop and moves the ship from one side of the screen
//			to the next. The thread sleeps for 0.5 seconds and then continues to 
//			update the game state, move the player and potenttially re-randomize
//			the planets.
int Level1::Update()
{

	bool gameEnd = false;
	bool miniGame = false;
	char choice;

	if (shipBase->GetXCoordinate() + gridWidth >= windowWidth)
	{
		shipBase->SetIsMoving(false);
		newGrid->CreateRandomCoordinates();
		NewSector();

	}
	else
	{
		if (Mouse::mouseX > 0 && Mouse::mouseY > 0 && !(shipBase->GetIsMoving()))
		{
			SetShipDestination(Mouse::mouseX, Mouse::mouseY);
		}
		else if (shipBase->GetIsMoving())
		{
			miniGame = PlanetTouched();
			gameEnd = CheckShipCollision();

			if(!miniGame)
			{
				SetShipPosition();
				shipBase->SetFirstMovement();
				IsMoveFinished();
				SetEnemyDest();
				SetEnemyPos();
			}
		}
	}
	if (gameEnd)
	{
		return GAME_END;
	}
	else if (miniGame)
	{
		return MINI_GAME;
	}
	else
	{
		return ALL_GOOD;
	}
}
void Level1::IsMoveFinished()
{
	if (fabs(shipBase->GetXCoordinate() - shipBase->GetXDest()) < 5 &&
		fabs(shipBase->GetYCoordinate() - shipBase->GetYDest() < 5))
	{
		shipBase->SetXCoordinate(shipBase->GetXDest());
		shipDetails->SetXCoordinate(shipDetails->GetXDest());
		shipBase->SetYCoordinate(shipBase->GetYDest());
		shipDetails->SetYCoordinate(shipDetails->GetYDest());

		enemyShip->SetXCoordinate(enemyShip->GetXCoordinate());
		enemyShip->SetYCoordinate(enemyShip->GetYCoordinate());

		shipBase->SetIsMoving(false);
		shipDetails->SetIsMoving(false);
	}
}
void Level1::SetShipPosition()
{
	shipBase->SetXCoordinate(shipBase->GetXCoordinate() + (shipBase->GetVector()->GetXRatio() * 5));
	shipDetails->SetXCoordinate(shipDetails->GetXCoordinate() + (shipDetails->GetVector()->GetXRatio() * 5));
	shipBase->SetYCoordinate(shipBase->GetYCoordinate() + (shipBase->GetVector()->GetYRatio() * 5));
	shipDetails->SetYCoordinate(shipDetails->GetYCoordinate() + (shipDetails->GetVector()->GetYRatio() * 5));
}

void Level1::SetEnemyPos(void)
{
	if (shipBase->GetIsMoving())
	{
		if (enemyShip->GetVector()->GetMagnitude() <= ((windowWidth / 20) * 4) ||
			enemyShip->GetVector()->GetMagnitude() <= ((windowHeight / 20) * 4))
		{
			enemyShip->SetXCoordinate(enemyShip->GetXCoordinate() + (enemyShip->GetVector()->GetXRatio() * 5.15));
			enemyShip->SetYCoordinate(enemyShip->GetYCoordinate() + (enemyShip->GetVector()->GetYRatio() * 5.15));
		}
		else
		{
			enemyShip->SetXCoordinate(enemyShip->GetXCoordinate() + (enemyShip->GetVector()->GetXRatio() * 4));
			enemyShip->SetYCoordinate(enemyShip->GetYCoordinate() + (enemyShip->GetVector()->GetYRatio() * 4));
		}

	}
}

void Level1::SetEnemyDest(void)
{
	enemyShip->SetXDest(shipBase->GetXCoordinate());
	enemyShip->SetYDest(shipBase->GetYCoordinate());

	enemyShip->GetVector()->XVectorLength(shipBase->GetXCoordinate(), enemyShip->GetXCoordinate());
	enemyShip->GetVector()->YVectorLength(shipBase->GetYCoordinate(), enemyShip->GetYCoordinate());

	enemyShip->GetVector()->FrameRatio(enemyShip->GetVector()->GetXVectorLength(), enemyShip->GetVector()->GetYVectorLength());
}

bool Level1::CheckShipCollision(void)
{
	bool gameEnd = false;
	if ((enemyShip->GetVector()->GetMagnitude() <= gridWidth && enemyShip->GetVector()->GetMagnitude() <= gridHeight) && !shipBase->GetFirstMovement())
	{
		if (shipBase->GetEnergy() - 300 <= 0)
		{
			shipBase->SetEnergy(shipBase->GetEnergy() - 300);
			gameEnd = true;
		}
		else
		{
			shipBase->SetEnergy(shipBase->GetEnergy() - 300);
		}
		NewSector();
		//newGrid->CreateRandomCoordinates();
		shipBase->SetYCoordinate(windowHeight / 2);
		shipDetails->SetYCoordinate(windowHeight / 2);
		enemyShip->SetYCoordinate(windowHeight / 2);
	}
	return gameEnd;
}

bool Level1::PlanetTouched(void)
{
	int i = 0;
	bool miniGameActivate = false;
	float planetLocation = 0.0;
	srand((unsigned)time(NULL));

	for (i = 0; i < newGrid->selectCoord.size(); i++)
	{
		if (shipBase->GetXCoordinate() == newGrid->selectCoord[i].first &&
			shipBase->GetYCoordinate() == newGrid->selectCoord[i].second && !miniGameActivate)
		{
			miniGameActivate = true;

			shipBase->SetTempEnergy((rand() % 300 + 1));
			shipBase->SetTempScience((rand() % 300 + 1));

			if (Mouse::keyboardSelection == 49 || Mouse::keyboardSelection == 97)
			{
				Mouse::keyboardSelection = 0;
				if (shipBase->GetEnergy() + shipBase->GetTempEnergy() >= 900)
				{
					shipBase->SetEnergy(900);
					shipBase->SetTempEnergy(0);
				}
				else
				{
					shipBase->SetEnergy(shipBase->GetEnergy() + shipBase->GetTempEnergy());
					shipBase->SetTempEnergy(0);
				}
			}

			if (Mouse::keyboardSelection == 50 || Mouse::keyboardSelection == 98)
			{
				Mouse::keyboardSelection = 0;
				shipBase->SetScience(shipBase->GetScience() + shipBase->GetTempScience());
				shipBase->SetTempScience(0);
			}

			if (Mouse::keyboardSelection == 51 || Mouse::keyboardSelection == 99)
			{
				Mouse::keyboardSelection = 0;
				Mouse::mouseX = 0;
				Mouse::mouseY = 0;
				shipBase->SetXCoordinate(shipBase->GetXCoordinate() + gridWidth + 1);
				shipDetails->SetXCoordinate(shipDetails->GetXCoordinate() + gridWidth + 1);
				SetShipDestination(shipBase->GetXCoordinate(), shipBase->GetYCoordinate());
				
				miniGameActivate = false;
			}
		}

		else if ((shipBase->GetXCoordinate() >= newGrid->selectCoord[i].first && shipBase->GetXCoordinate() <= newGrid->selectCoord[i].first + gridWidth) &&
			(shipBase->GetYCoordinate() >= newGrid->selectCoord[i].second && shipBase->GetYCoordinate() <= newGrid->selectCoord[i].second + gridHeight))
		{
			shipBase->SetXCoordinate(newGrid->selectCoord[i].first);
			shipBase->SetYCoordinate(newGrid->selectCoord[i].second);
			shipDetails->SetXCoordinate(newGrid->selectCoord[i].first);
			shipDetails->SetYCoordinate(newGrid->selectCoord[i].second);

			miniGameActivate = true;
			break;
		}
	}
	return miniGameActivate;
}

void Level1::NewSector(void)
{

	//Get rid of Vecor class.

	shipBase->SetXCoordinate(0.0);
	//shipBase->SetYCoordinate(windowHeight / 2);
	shipBase->SetXDest(shipBase->GetXCoordinate());
	shipBase->SetYDest(shipBase->GetYCoordinate());
	shipBase->GetVector()->FrameRatio(0, 0);
	shipDetails->GetVector()->FrameRatio(0, 0);
	shipDetails->SetXCoordinate(0.0);
	//shipDetails->SetYCoordinate(windowHeight / 2);
	shipDetails->SetXDest(shipDetails->GetXCoordinate());
	shipDetails->SetYDest(shipDetails->GetYCoordinate());

	enemyShip->SetXCoordinate(windowWidth - gridWidth);
	//enemyShip->SetYCoordinate(windowHeight / 2);
	enemyShip->SetXDest(shipBase->GetXCoordinate());
	enemyShip->SetYDest(shipBase->GetYCoordinate());
	enemyShip->GetVector()->FrameRatio(0, 0);
	
	Mouse::mouseX = 0.0;
	Mouse::mouseY = 0.0;

	IsMoveFinished();
}

void Level1::SetShipDestination(float x, float y)
{
	shipBase->SetXDest(x);
	shipDetails->SetXDest(x);
	shipBase->SetYDest(y);
	shipDetails->SetYDest(y);

	shipBase->GetVector()->XVectorLength(shipBase->GetXDest(), shipBase->GetXCoordinate());
	shipDetails->GetVector()->XVectorLength(shipDetails->GetXDest(), shipDetails->GetXCoordinate());
	shipBase->GetVector()->YVectorLength(shipBase->GetYDest(), shipBase->GetYCoordinate());
	shipDetails->GetVector()->YVectorLength(shipDetails->GetYDest(), shipDetails->GetYCoordinate());

	shipBase->GetVector()->FrameRatio(shipBase->GetVector()->GetXVectorLength(), shipBase->GetVector()->GetYVectorLength());
	shipDetails->GetVector()->FrameRatio(shipDetails->GetVector()->GetXVectorLength(), shipDetails->GetVector()->GetYVectorLength());

	shipBase->SetOrientation();
	shipDetails->SetOrientation();

	shipBase->SetIsMoving(true);
	shipDetails->SetIsMoving(true);
}

float Level1::GetWindowWidth(void)
{
	return windowWidth;
}
float Level1::GetWindowHeight(void)
{
	return windowHeight;
}

void Level1::SetWindowWidth(float width)
{
	windowWidth = width;

}

void Level1::SetWindowHeight(float height)
{
	windowHeight = height;
}


void Level1::Render(bool miniGame)
{
	int i = 0;
	float xCoord = 0.0;
	float yCoord = 0.0;
	int gridPlacement = 0;

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);

	background->DrawBackground(windowWidth, windowHeight);

	if (miniGame)
	{
		
		miniGameLayout->DrawMiniGame(windowWidth / 3, windowHeight / 3);

		for (int i = 0; i < newGrid->selectCoord.size(); i++)
		{

			if (newGrid->PlanetLocations[i].second == 1 && (newGrid->selectCoord[i].first == shipBase->GetXCoordinate()) && (newGrid->selectCoord[i].second == shipBase->GetYCoordinate()))
			{
				planet1->DrawPlanet(((windowWidth / 3) + (gridWidth / 5)), ((windowHeight / 3) + (gridHeight / 2)));
				break;
			}
			if (newGrid->PlanetLocations[i].second == 2 && (newGrid->selectCoord[i].first == shipBase->GetXCoordinate()) && (newGrid->selectCoord[i].second == shipBase->GetYCoordinate()))
			{
				planet2->DrawPlanet(((windowWidth / 3) + (gridWidth / 5)), ((windowHeight / 3) + (gridHeight / 2)));
				break;
			}
			if (newGrid->PlanetLocations[i].second == 3 && (newGrid->selectCoord[i].first == shipBase->GetXCoordinate()) && (newGrid->selectCoord[i].second == shipBase->GetYCoordinate()))
			{
				planet3->DrawPlanet(((windowWidth /3) + (gridWidth /5)), ((windowHeight / 3) + (gridHeight / 2)));
				break;
			}
		}
	}
	else
	{
		newGrid->PlanetRandomize(planet1, planet2, planet3);
		shipBase->Draw(shipBase->GetXCoordinate(), shipBase->GetYCoordinate(), shipBase->GetOrientation());
		shipDetails->Draw(shipDetails->GetXCoordinate(), shipDetails->GetYCoordinate(), shipDetails->GetOrientation());
		enemyShip->Draw(enemyShip->GetXCoordinate(), enemyShip->GetYCoordinate(), enemyShip->GetOrientation());
	}

}

