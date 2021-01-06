#include "BackGroundManager.h"
#include "Renderer.h"
#include "SDL.h"
#include "include/SDL_ttf.h"
#include "SDL_image.h"

BackGroundScreenManager::BackGroundScreenManager(const std::shared_ptr<Renderer>& renderer, int numLives)
    :
    m_renderer(renderer),
    m_numDefenderLives(numLives)
{
    auto xPos = 30.0f;
   
    for (int i = 0; i < m_numDefenderLives; i++) {
        m_defenderLivesRectangle.push_back(Rectangle({ xPos,yPos }, 255, 0, 0, 255, width, height, m_renderer));
        xPos += 60;
    }

    //Initialize the ttf engine
    TTF_Init();

    //create highscore and score textures
    m_playerScoreTexture = CreateTextTexture("Score:");
    m_playerHighscoreTexture = CreateTextTexture("Highscore:");
    m_gameOverTexture = CreateTextTexture("GAME OVER", 255, 0, 0);
    m_playAgainOrQuitTexture = CreateTextTexture("Press Enter to play again or Escape to quit.");

    //Create player life texture
    m_playerLivesTexture = IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\Defender.png)");
}

BackGroundScreenManager::~BackGroundScreenManager() {
    SDL_DestroyTexture(m_playerScoreTexture);
    SDL_DestroyTexture(m_playerHighscoreTexture);
    SDL_DestroyTexture(m_gameOverTexture);
    SDL_DestroyTexture(m_playAgainOrQuitTexture);
    SDL_DestroyTexture(m_playerLivesTexture);

    TTF_Quit(); 
}

void BackGroundScreenManager::Show() {
   
    for (auto& rect : m_defenderLivesRectangle) {
        auto point = rect.GetPoint();

        CopyTextureToRenderer(m_playerLivesTexture, rect.GetWidth(), rect.GetHeight(), point.x, point.y);
    }

    //Print the score and highScore to the Console window  
    CopyTextureToRenderer(m_playerScoreTexture, 100, 50, 0,0);
    CopyTextureToRenderer(m_playerHighscoreTexture,150, 50, 200, 0);
   
    auto playerScoreValueTexture = CreateTextTexture(std::to_string(m_playerScore));
    CopyTextureToRenderer(playerScoreValueTexture, 50, 50, 110, 0);

    auto playerHighscoreValueTexture = CreateTextTexture(std::to_string(m_playerHighscore));
    CopyTextureToRenderer(playerHighscoreValueTexture, 50, 50, 360, 0);
}

int BackGroundScreenManager::ShowGameOverDisplay() {
    while (!m_gameOverReturnCode) {
        HandleGameOverUserInput();
        ClearScreen();
        CopyTextureToRenderer(m_gameOverTexture, 300, 200, 250, 150);
        CopyTextureToRenderer(m_playAgainOrQuitTexture, 700, 200, 50, 350);
        m_renderer->Present();
    }
    SDL_Delay(500);
    return m_gameOverReturnCode;
}

void BackGroundScreenManager::HandleGameOverUserInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {}

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        m_gameOverReturnCode = ReturnCode::Quit;
    }
    else if (state[SDL_SCANCODE_RETURN]) {
        m_gameOverReturnCode = ReturnCode::PlayAgain;
    }
}

//Removes one of the lives from the m_defenderLivesRectangle so that the player
//can get a visual of how many lives is left for the defender.
void BackGroundScreenManager::DefenderHit() {
    //The defender was hit, so remove one of the defenderLivesRectangles to indicate to the player that he
    //is down one life.
    m_defenderLivesRectangle.pop_back();
}

//Clears the screen with the default color black
void BackGroundScreenManager::ClearScreen() {
    m_renderer->SetColor(0, 0, 0, 255);
    m_renderer->Clear();
}

void BackGroundScreenManager::Reset() {
    m_defenderLivesRectangle.clear();

    auto xPos = 30.0f;
   
    for (int i = 0; i < m_numDefenderLives; i++) {
        m_defenderLivesRectangle.push_back(Rectangle({ xPos,yPos }, 255, 0, 0, 255, width, height, m_renderer));
        xPos += 60;
    }

    m_gameOverReturnCode = 0;
}

//Copies the texture to the renderer
void BackGroundScreenManager::CopyTextureToRenderer(SDL_Texture* texture, int width, int height, int xPos, int yPos) {
    SDL_Rect rect;
    rect.x = xPos;
    rect.y = yPos;
    rect.w = width;
    rect.h = height;

    SDL_RenderCopy(m_renderer->GetSDLRenderer(), texture, nullptr, &rect);
}

//Creates a SDL_Texture containing the text given as the argument
SDL_Texture* BackGroundScreenManager::CreateTextTexture(const std::string& text, int r, int g, int b) {
    auto font = TTF_OpenFont(R"(Resources\arial.ttf)", 46);
    SDL_Color textColor = { r,g,b };
      
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.data(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);

    //destroy the surface since we have no further use of it
    SDL_FreeSurface(surface);

    return texture;
}

void BackGroundScreenManager::Update(int score) {
    m_playerScore = score;

    if (m_playerScore > m_playerHighscore) {
        m_playerHighscore = m_playerScore;
    }
}
