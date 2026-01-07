/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Creator
*/

#include "Game.hpp"
#include "Creator.hpp"
#include "GameHelper.hpp"
#include "ScriptsHandler.hpp"

#include "HP.hpp"
#include "Tag.hpp"
#include "Data.hpp"
#include "Text.hpp"
#include "Scale.hpp"
#include "Layer.hpp"
#include "Group.hpp"
#include "Scene.hpp"
#include "Audio.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Script.hpp"
#include "Damage.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Animator.hpp"
#include "Rotation.hpp"
#include "GuiWidget.hpp"
#include "SoundEffect.hpp"
#include "BoxCollider.hpp"
#include "RectangleShape.hpp"

Creator::Creator(World& world)
: _world(world)
{
}

/**
 * @brief Create a beautiful Main Menu using TGUI wrapped in ECS
 */
void Creator::createTguiMenu()
{
    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;

    auto menuRoot = _world.createEntity();
    menuRoot->addComponent<Scene>(2);
    menuRoot->addComponent<Tag>("menu_root");
    menuRoot->addComponent<GuiWidget>(WidgetType::PANEL);

    auto guiRoot = menuRoot->getComponent<GuiWidget>();
    guiRoot->setSize(static_cast<float>(width), static_cast<float>(window->getSize().y));
    guiRoot->setPosition(0.f, 0.f);
    guiRoot->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(10, 10, 30, 200));

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, "R-TYPE", menuRoot->getId());
    titleEntity->addComponent<Scene>(2);
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    titleEntity->addComponent<Tag>("menu_title");
    titleEntity->getComponent<GuiWidget>()->setFont("../assets/font/title.ttf");
    titleEntity->addComponent<Position>(centerX - titleEntity->getComponent<GuiWidget>()->getSize().x / 2.0f, 100.f);
    
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setTextSize(100);
    guiTitle->setTextColor(sf::Color::Cyan);
    guiTitle->setTextStyle(tgui::TextStyle::Bold);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition(centerX, 150.f);

    auto styleNeonButton = [](std::shared_ptr<GuiWidget> gui) {
        auto renderer = gui->getRawWidget()->getRenderer();
        renderer->setProperty("BackgroundColor", tgui::Color(20, 20, 40, 200));
        renderer->setProperty("BackgroundColorHover", tgui::Color(40, 40, 80, 255));
        renderer->setProperty("TextColor", tgui::Color::White);
        renderer->setProperty("TextColorHover", tgui::Color::Cyan);
        renderer->setProperty("BorderColor", tgui::Color::Cyan);
        renderer->setProperty("BorderColorHover", tgui::Color::White);
        renderer->setProperty("Borders", tgui::Borders(2));
        renderer->setProperty("RoundedBorderRadius", 10);
        gui->getRawWidget()->setMouseCursor(tgui::Cursor::Type::Hand);
    };

    auto btnPlay = _world.createEntity();
    btnPlay->addComponent<GuiWidget>(WidgetType::BUTTON, "START", menuRoot->getId());
    btnPlay->addComponent<Scene>(2);
    btnPlay->addComponent<Layer>(LayerType::UI + 1);
    btnPlay->addComponent<Tag>("menu_button_play");
    
    auto guiPlay = btnPlay->getComponent<GuiWidget>();
    styleNeonButton(guiPlay);
    guiPlay->setFont("../assets/font/title.ttf");
    guiPlay->setCallback([this]() {
        auto music = GameHelper::getEntityByTag(_world, "music");
        if (music) {
            auto musicComp = music->getComponent<Music>();
            if (musicComp)
            musicComp->stop();
        }
        _world.setCurrentScene(1); 
    });
    guiPlay->setSize(400.f, 120.f);
    guiPlay->setOrigin(0.5f, 0.5f);
    guiPlay->setPosition("50%", "50%");

    auto btnQuit = _world.createEntity();
    btnQuit->addComponent<GuiWidget>(WidgetType::BUTTON, "EXIT", menuRoot->getId());
    btnQuit->addComponent<Scene>(2);
    btnQuit->addComponent<Layer>(LayerType::UI + 1);
    btnQuit->addComponent<Tag>("menu_button_quit");


    auto guiQuit = btnQuit->getComponent<GuiWidget>();
    styleNeonButton(guiQuit);
    guiQuit->getRawWidget()->getRenderer()->setProperty("BorderColor", tgui::Color(255, 50, 50));
    guiQuit->setCallback([this]() {
        if (_world.getWindow())
            _world.getWindow()->close();
    });
    guiQuit->setFont("../assets/font/title.ttf");
    guiQuit->setSize(400.f, 120.f);
    guiQuit->setPosition("50%", "80%");
    guiQuit->setOrigin(0.5f, 0.5f);

    auto guiOptions = _world.createEntity();
    guiOptions->addComponent<GuiWidget>(WidgetType::BUTTON, "OPTIONS", menuRoot->getId());
    guiOptions->addComponent<Scene>(2);
    guiOptions->addComponent<Layer>(LayerType::UI + 1);
    guiOptions->addComponent<Tag>("menu_button_options");

    auto guiOpt = guiOptions->getComponent<GuiWidget>();
    styleNeonButton(guiOpt);
    guiOpt->setFont("../assets/font/title.ttf");
    guiOpt->setSize(400.f, 120.f);
    guiOpt->setOrigin(0.5f, 0.5f);
    guiOpt->setPosition("50%", "65%");
    guiOpt->setCallback([this]() {
        _world.setCurrentScene(3);
    });

    createTguiOptions();
}

/**
 * @brief Create a status text entity for options menu
 * @param y The y position
 * @param initialState The initial state (on/off)
 * @return The created entity
 */
std::shared_ptr<Entity> Creator::createStatusText(float y, bool initialState)
{
    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;

    auto statusEntity = _world.createEntity();
    statusEntity->addComponent<Scene>(3);
    statusEntity->addComponent<Layer>(LayerType::UI);
    
    std::string label = initialState ? "ON" : "OFF";
    statusEntity->addComponent<Text>(label, "../assets/font/title.ttf", 30);
    
    sf::Color color = initialState ? sf::Color::Green : sf::Color::Red;
    statusEntity->getComponent<Text>()->setColor(color);

    statusEntity->addComponent<Position>(centerX + 250.f, y + 15.f);
    return statusEntity;
}

void Creator::createTguiOptions()
{
    auto optionsRoot = _world.createEntity();
    optionsRoot->addComponent<Scene>(3);
    optionsRoot->addComponent<Layer>(LayerType::UI);
    optionsRoot->addComponent<Position>(0.f, 0.f);
    optionsRoot->addComponent<Tag>("options_root");
    optionsRoot->addComponent<GuiWidget>(WidgetType::PANEL);
    
    auto rootGui = optionsRoot->getComponent<GuiWidget>();
    rootGui->setSize("100%", "100%");
    rootGui->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(10, 10, 30, 240));

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, "OPTIONS", optionsRoot->getId());
    titleEntity->addComponent<Scene>(3);
    titleEntity->addComponent<Tag>("options_title");
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/title.ttf");
    guiTitle->setTextSize(80);
    guiTitle->setTextColor(sf::Color::Green);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "10%");

    auto mainLayoutEntity = _world.createEntity();
    mainLayoutEntity->addComponent<GuiWidget>(WidgetType::VERTICAL_LAYOUT, "", optionsRoot->getId());
    mainLayoutEntity->addComponent<Scene>(3);
    mainLayoutEntity->addComponent<Tag>("options_main_layout");
    mainLayoutEntity->addComponent<Layer>(LayerType::UI + 1);

    auto guiMainLayout = mainLayoutEntity->getComponent<GuiWidget>();
    guiMainLayout->setSize("60%", "60%");
    guiMainLayout->setOrigin(0.5f, 0.5f);
    guiMainLayout->setPosition("50%", "50%");

    auto createOptionToggle = [this, mainLayoutEntity](const std::string& label, bool& stateValue) {
        printf("Creating option toggle: %s\n", label.c_str());
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(3);
        rowEntity->addComponent<Tag>("option_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "100");

        auto btnEntity = _world.createEntity();
        btnEntity->addComponent<GuiWidget>(WidgetType::BUTTON, label, rowEntity->getId());
        btnEntity->addComponent<Scene>(3);
        btnEntity->addComponent<Tag>("option_button");
        auto guiBtn = btnEntity->getComponent<GuiWidget>();
        guiBtn->setSize("50%", "70%");
        guiBtn->setOrigin(0.5f, 0.5f);
        guiBtn->setPosition("30%", "50%");
        guiBtn->setFont("../assets/font/title.ttf");

        auto statusEntity = _world.createEntity();
        statusEntity->addComponent<GuiWidget>(WidgetType::LABEL, stateValue ? "ON" : "OFF", rowEntity->getId());
        statusEntity->addComponent<Scene>(3);
        statusEntity->addComponent<Tag>("option_status");
        auto guiStatus = statusEntity->getComponent<GuiWidget>();
        guiStatus->setTextSize(30);
        guiStatus->setOrigin(0.5f, 0.5f);
        guiStatus->setPosition("80%", "50%");
        guiStatus->setTextColor(stateValue ? sf::Color::Green : sf::Color::Red);

        guiBtn->setCallback([&stateValue, guiStatus]() {
            stateValue = !stateValue;
            guiStatus->setText(stateValue ? "ON" : "OFF");
            guiStatus->setTextColor(stateValue ? sf::Color::Green : sf::Color::Red);
        });
    };

    static bool godMode = false;
    static bool easyMode = false;
    static bool hardMode = false;
    static bool colorBlindMode = false;
    
    createOptionToggle("GOD MODE", godMode);
    createOptionToggle("EASY MODE", easyMode);
    createOptionToggle("HARD MODE", hardMode);
    createOptionToggle("COLOR BLIND MODE", colorBlindMode);

    // 4. BOUTON RETOUR
    auto btnReturn = _world.createEntity();
    btnReturn->addComponent<GuiWidget>(WidgetType::BUTTON, "BACK TO MENU", optionsRoot->getId());
    btnReturn->addComponent<Scene>(3);
    btnReturn->addComponent<Layer>(LayerType::UI + 2);
    btnReturn->addComponent<Tag>("options_button_return");
    auto guiReturn = btnReturn->getComponent<GuiWidget>();
    guiReturn->setSize(200, 60);
    guiReturn->setOrigin(0.5f, 0.5f);
    guiReturn->setPosition("50%", "90%");
    guiReturn->setCallback([this]() { _world.setCurrentScene(2); });
}

/**
 * @brief Creates the player entity.
 * 
 * This function initializes the player entity with necessary components.
 */
void Creator::createPlayer(uint64_t id)
{
    if (GameHelper::getEntityById(_world, id) != nullptr)
        return;
    static int playerCount = 0;
    if (playerCount >= 4)
        return;
    auto player = _world.createEntity(id);
    player->addComponent<HP>(100);
    player->addComponent<Position>(75.0f, 75.0f);
    player->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet42.gif"));
    player->addComponent<Scale>(2.f);
    player->addComponent<Scene>(1);
    player->addComponent<SoundEffect>(std::string("../assets/sounds/lazershoot.mp3"));
    player->addComponent<Layer>(10);
    player->addComponent<Group>(playerCount + 1);
    player->addComponent<Damage>(10);
    player->addComponent<BoxCollider>(33.0f, 19.0f);

    std::map<std::string, std::string> dataMap = {
        {"is_god_mode", "false"},
        {"is_easy_mode", "false"},
        {"is_color_blind", "false"},
        {"is_hard_mode", "false"}
    };
    player->addComponent<Data>(dataMap);
    
    if (playerCount == 0) {
        player->addComponent<Velocity>(0.f, 0.f);
        player->addComponent<Animator>(2, 1, 3.f, 0, 0, 33, 19, 0, 0);
        player->addComponent<Tag>("player");
    } else {
        player->addComponent<Animator>(2, 1, 3.f, 0, (playerCount * 17), 33, 19, 0, 0);
        player->addComponent<Tag>("player_mate");
    }

    playerCount++;
    auto fire = _world.createEntity();
    fire->addComponent<Position>(0.f, 85.f);
    fire->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    fire->addComponent<Animator>(2, 1, 3.f, 285, 85, 15, 15, 0, 0);
    fire->addComponent<Scale>(2.f);
    fire->addComponent<Scene>(1);
    fire->addComponent<Script>(playerfire);
    fire->addComponent<Music>("../assets/sounds/game.mp3", 100.f, true);
    fire->addComponent<Group>(playerCount);
    fire->addComponent<Layer>(10);
    fire->addComponent<Tag>("fire");
}

/**
 * @brief Create Background
 * This function initializes the background entities with necessary components.
*/
void Creator::createBackground(sf::RenderWindow& window)
{
    auto backgroundFirst = _world.createEntity();
    backgroundFirst->addComponent<Sprite>(std::string("../assets/sprites/background.png"));
    
    auto windowSize = window.getSize();
    auto spriteComp = backgroundFirst->getComponent<Sprite>();
    auto boundsSize = spriteComp->getSprite()->getGlobalBounds(); 
    float scaleX = static_cast<float>(windowSize.x) / boundsSize.size.x;
    float scaleY = static_cast<float>(windowSize.y) / boundsSize.size.y;
    float finalScale = std::max(scaleX, scaleY);
    if (finalScale < 1.0f)
        finalScale = 1.0f;
    backgroundFirst->addComponent<Scale>(finalScale);

    backgroundFirst->addComponent<Scene>(_world.getCurrentScene());
    backgroundFirst->addComponent<Position>(0.f, 0.f);
    backgroundFirst->addComponent<Script>(backgroundScrollScript);
    backgroundFirst->addComponent<Layer>(LayerType::BACKGROUND);
    backgroundFirst->addComponent<Velocity>(-5.f, 0.f);
    backgroundFirst->addComponent<Tag>("background_first");
    auto backgroundSecond = _world.createEntity();
    backgroundSecond->addComponent<Sprite>(std::string("../assets/sprites/background.png"));
    backgroundSecond->addComponent<Scale>(1.f);
    backgroundSecond->addComponent<Scene>(_world.getCurrentScene());
    auto bounds = backgroundFirst->getComponent<Sprite>()->getSprite()->getGlobalBounds();
    backgroundSecond->addComponent<Position>(bounds.size.x - 10.f, 0.f);
    backgroundSecond->addComponent<Velocity>(-5.f, 0.f);
    backgroundSecond->addComponent<Script>(backgroundScrollScript);
    backgroundSecond->addComponent<Layer>(LayerType::BACKGROUND);
    backgroundSecond->addComponent<Tag>("background_second");
}

/**
 * @brief Create Enemy
 * This function initializes an enemy entity with necessary components.
*/
void Creator::createEnemy(float x, float y, int type)
{
    enum EnemyType {
        BASIC = 1,
        FAST,
        TANK
    };
    switch (type) {
        case BASIC:
            GameHelper::createBasicEnemy(_world, x, y);
            break;
        case FAST:
            // Implement fast enemy creation
            break;
        case TANK:
            // Implement tank enemy creation
            break;
        default:
            std::cerr << "Unknown enemy type: " << type << std::endl;
            break;
    }
}

/**
 * @brief Create Camera
 * This function initializes a camera entity with necessary components.
*/
void Creator::createCamera()
{
    auto cameraEntity = _world.createEntity();
    cameraEntity->addComponent<Camera>(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f));
    cameraEntity->addComponent<Tag>("main_camera");
}


/**
 * @brief Creates a bullet entity.
 *
 * This function initializes a bullet entity with necessary components.
 * @param entityId The ID of the entity that fired the bullet.
 */
void Creator::createBullet(size_t entityId, int x, int y, int type)
{
    auto entity = GameHelper::getEntityById(_world, entityId);
    if (entity)
        return;
    bool isPlayer = (type == Bullet);
    auto bullet = _world.createEntity(entityId);
    if (isPlayer) {
        bullet->addComponent<Position>(x, y);
        bullet->addComponent<Velocity>(10.f, 0.f);
        bullet->addComponent<Animator>(2, 1, 3.0f, 200, 120, 32, 15, 0, 0);
    } else {
        bullet->addComponent<Position>(x - 20.f , y + 15.f);
        bullet->addComponent<Rotation>(180.f);
        bullet->addComponent<Velocity>(-10.f, 0.f);
    }
    bullet->addComponent<Sprite>(std::string("../assets/sprites/r-typesheet1.gif"));
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<Tag>("bullet");
}

/**
 * @brief Creates the loading screen entities.
 *
 * This function initializes the loading screen with text and a progress bar.
 */
void Creator::createLoadingScreen()
{
    auto window = _world.getWindow();
    float centerX = window->getSize().x / 2.0f - 200.f;
    float centerY = window->getSize().y / 2.0f;

    auto title = _world.createEntity();
    title->addComponent<Scene>(0);
    title->addComponent<Text>("LOADING...", "../assets/font/title.ttf", 40);
    title->addComponent<Position>(centerX - title->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, centerY - 100.f);
    title->addComponent<Layer>(LayerType::UI);

    auto status = _world.createEntity();
    status->addComponent<Scene>(0);
    status->addComponent<Text>("Initializing...", "../assets/font/title.ttf", 20);
    status->addComponent<Position>(centerX - status->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, centerY + 60.f);
    status->addComponent<Layer>(LayerType::UI);
    status->getComponent<Text>()->setColor(sf::Color(200, 200, 200));
    status->addComponent<Tag>("loading_status");

    auto bgBar = _world.createEntity();
    bgBar->addComponent<Scene>(0);
    bgBar->addComponent<Position>(centerX - 200.f, centerY);
    bgBar->addComponent<RectangleShape>(400.f, 20.f, 50, 50, 50, 255);
    bgBar->addComponent<Tag>("loading_bg_bar");
    bgBar->addComponent<Scale>(1.f);
    bgBar->addComponent<Layer>(LayerType::UI);

    auto fillBar = _world.createEntity();
    fillBar->addComponent<Scene>(0);
    fillBar->addComponent<Position>(centerX - 200.f, centerY);
    fillBar->addComponent<RectangleShape>(1.f, 20.f, 100, 250, 50, 255);
    fillBar->addComponent<Layer>(LayerType::UI + 1);
    fillBar->addComponent<Tag>("loading_bar");
    fillBar->addComponent<Scale>(1.f);
}
