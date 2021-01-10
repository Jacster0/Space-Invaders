#include "BackGroundManager.h"
#include "Renderer.h"
#include "SDL.h"
#include "include/SDL_ttf.h"
#include "SDL_image.h"
#include "Star.h"
#include <random>

BackGroundScreenManager::BackGroundScreenManager(const std::shared_ptr<Renderer>& renderer, int numLives)
    :
    m_renderer(renderer),
    m_numDefenderLives(numLives)
{
    auto xPos = 30.0f;
   
    for (int i = 0; i < m_numDefenderLives; i++) {
        m_defenderLives.push_back(std::make_unique<Rectangle>(
            Point2D(xPos,m_yPos), 
            255, 0, 0, 255, 
            m_width, m_height,
            m_renderer));
        xPos += 60;
    }

    //Initialize the ttf engine
    TTF_Init();

    //create highscore and score textures
    SDL_Rect rect;
    rect.w = 400;
    rect.h = 100;
    rect.x = 110;
    rect.y = 0;

    m_font = TTF_OpenFont(R"(Resources\Fonts\arial.ttf)", 46);

    //m_playerScoreValueTexture = this->CreateTextTexture(std::to_string(m_playerScore));
    m_playerScoreTexture     = CreateTextTexture("Score:");
    m_playerHighscoreTexture = CreateTextTexture("Highscore:");
    m_gameOverTexture        = CreateTextTexture("GAME OVER", 255, 0, 0);
    m_playAgainOrQuitTexture = CreateTextTexture("Press Enter to play again or Escape to quit.");

    //Create player life texture
    m_playerLivesTexture = IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\Textures\Defender.png)");

    CreateStarField();
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
   
    DrawStarField();

    for (const auto& shape : m_defenderLives) {
        if (auto rect = dynamic_cast<Rectangle*>(shape.get())) {
            auto point = rect->GetPoint();

            CopyTextureToRenderer(m_playerLivesTexture, rect->GetWidth(), rect->GetHeight(), point.x, point.y);
        }
    }

    //Print the score and highScore to the window  
    CopyTextureToRenderer(m_playerScoreTexture, 100, 50, 0,0);
    CopyTextureToRenderer(m_playerHighscoreTexture,150, 50, 200, 0);

    auto playerHighScoreValueTexture = CreateTextTexture(std::to_string(m_playerHighscore));
    CopyTextureToRenderer(playerHighScoreValueTexture, 80, 50, 350, 0);

    auto playerScoreValueTexture = CreateTextTexture(std::to_string(m_playerScore));
    CopyTextureToRenderer(playerScoreValueTexture, 80, 50, 110, 0);

    SDL_DestroyTexture(playerScoreValueTexture);
    SDL_DestroyTexture(playerHighScoreValueTexture);
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
    m_defenderLives.pop_back();
}

//Clears the screen with the default color black
void BackGroundScreenManager::ClearScreen() {
    m_renderer->SetColor(0, 0, 0, 255);
    m_renderer->Clear();
}

void BackGroundScreenManager::CreateStarField() {
    std::random_device device;
    std::default_random_engine rng(device());

    //Generate between 10 to 20 stars
    std::uniform_int_distribution<int>    numStarsDist(5, 11);
    std::uniform_int_distribution<int>    innerCircleRadius(7, 13);
    std::uniform_int_distribution<int>    outerCircleRadius(16, 22);
    std::uniform_real_distribution<float> starXPos(5, 770);
    std::uniform_real_distribution<float> starYPos(100, 150);
    std::uniform_int_distribution<int>    numFlares(4, 11);

    const auto numStars = numStarsDist(rng);

    for (int i = 0; i < numStars; i++) {
        m_starField.push_back(std::make_unique<Star>(
            Point2D(starXPos(rng), starYPos(rng)),
            innerCircleRadius(rng),
            outerCircleRadius(rng),
            numFlares(rng),
            m_renderer
            ));
    }

    for (int i = 0; i < numStars; i++) {
        for (auto& shape : m_starField) {
            if (auto star = dynamic_cast<Star*>(shape.get())) {
                m_originalStars.push_back(*star);
            }
        }
    }
}

void BackGroundScreenManager::DrawStarField() {
    for (const auto& shape : m_starField) {
        shape->render(RenderFlag::OutLine);
    }
}

void BackGroundScreenManager::UpdateStarField() {
    ScaleStarField();
}

int BackGroundScreenManager::GetHighScore() const noexcept {
    return m_playerHighscore;
}

void BackGroundScreenManager::SetHighScore(int highScore) noexcept {
    m_playerHighscore = highScore;
}

void BackGroundScreenManager::Reset(bool playerWon) {
    if (!playerWon) {
        m_defenderLives.clear();

        auto xPos = 30.0f;

        for (int i = 0; i < m_numDefenderLives; i++) {
            m_defenderLives.push_back(std::make_unique<Rectangle>(
                Point2D(xPos,m_yPos), 
                255, 0, 0, 255, 
                m_width, m_height,
                m_renderer));
            xPos += 60;
        }
    }
    m_gameOverReturnCode = 0;
}

void BackGroundScreenManager::ScaleStarField() {
    //Im using a sine wave to create a nice motion of upscaling/downscaling the stars
    //Amplitude * sin(2 * pi * frequency * time + phase) + 
    const float timeInSeconds = static_cast<float>(SDL_GetTicks()) / 1000.0f;
    const float scaleFactor = m_sineWaveAmplitude * sin(twoPi * m_sineWaveFrequency * timeInSeconds + m_sineWavePhase) + m_sineWaveOffsetY;

    for (int i = 0; i < m_starField.size(); i++) {
        if (Star* star = dynamic_cast<Star*>(m_starField.at(i).get())) {
            star->SetScale(1.0f * scaleFactor);
            star->Scale(m_originalStars.at(i));
        }
    }
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
    SDL_Color textColor = { r,g,b };

    auto surf = TTF_RenderText_Solid(m_font, text.c_str(), { 255,255,255 });
    auto texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surf);

    //destroy the surface since we have no further use of it
    SDL_FreeSurface(surf);

    return texture;
}

void BackGroundScreenManager::Update(int score) {
    UpdateStarField();

    m_playerScore = score;

    if (m_playerScore > m_playerHighscore) {
        m_playerHighscore = m_playerScore;
    }
}
