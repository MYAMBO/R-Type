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


static void styleNeonButton(std::shared_ptr<GuiWidget> gui)
{
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
}

static void styleNeonRow(std::shared_ptr<GuiWidget> gui)
{
    auto renderer = gui->getRawWidget()->getRenderer();
    renderer->setProperty("BackgroundColor", tgui::Color(15, 15, 30, 150));
    renderer->setProperty("Borders", tgui::Borders(1));
    renderer->setProperty("BorderColor", tgui::Color::Cyan);
    renderer->setProperty("RoundedBorderRadius", 5);
}

static void styleNeonSlider(std::shared_ptr<GuiWidget> gui)
{
    auto renderer = gui->getRawWidget()->getRenderer();
    renderer->setProperty("TrackColor", tgui::Color(20, 20, 40, 200));
    renderer->setProperty("TrackColorHover", tgui::Color(40, 40, 80, 255));
    renderer->setProperty("ThumbColor", tgui::Color::Cyan);
    renderer->setProperty("ThumbColorHover", tgui::Color::White);
    renderer->setProperty("BorderColor", tgui::Color::Cyan);
}


Creator::Creator(World& world)
: _world(world)
{
}

void Creator::createMyambo()
{
    auto window = _world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    auto myambo = _world.createEntity();
    myambo->addComponent<Text>("MYAMBO", "../assets/font/title.ttf", 10);
    myambo->getComponent<Text>()->setColor(255, 255, 255, 255);
    myambo->addComponent<Scene>(10);
    myambo->addComponent<Layer>(2);
    myambo->addComponent<Tag>("logo_myambo");
    myambo->addComponent<SoundEffect>("../assets/sounds/logo.mp3", 100.f);
    myambo->addComponent<Position>(centerX , centerY);

    auto myamboGlow = _world.createEntity();
    myamboGlow->addComponent<Scene>(10);
    myamboGlow->addComponent<Layer>(1);
    myamboGlow->addComponent<Position>(myambo->getComponent<Position>()->getX(), myambo->getComponent<Position>()->getY());
    myamboGlow->addComponent<Text>("MYAMBO", "../assets/font/title.ttf", 10);
    myamboGlow->addComponent<Tag>("logo_myambo_glow");
    myamboGlow->addComponent<Script>(myamboGlowScript);
    myambo->addComponent<Script>(myamboScript);

    auto prod = _world.createEntity();
    prod->addComponent<Text>("PRODUCTION", "../assets/font/title.ttf", 60);
    prod->getComponent<Text>()->setColor(0, 0, 0, 255);
    prod->getComponent<Text>()->setSize(60);
    prod->addComponent<Scene>(10);
    prod->addComponent<Layer>(2);
    prod->addComponent<Tag>("logo_production");
    prod->addComponent<SoundEffect>("../assets/sounds/production.mp3", 100.f);
    prod->addComponent<Position>(centerX , centerY + 220.f);
    std::map<std::string, std::string> dataMap = {{"displayed", "false"}};
    prod->addComponent<Data>(dataMap);
    prod->addComponent<Script>(productionScript);

    auto prodGlow = _world.createEntity();
    prodGlow->addComponent<Scene>(10);
    prodGlow->addComponent<Layer>(1);
    prodGlow->addComponent<Position>(prod->getComponent<Position>()->getX(), prod->getComponent<Position>()->getY());
    prodGlow->addComponent<Text>("PRODUCTION", "../assets/font/title.ttf", 60);
    prodGlow->getComponent<Text>()->setColor(0, 0, 0, 255);
    prodGlow->addComponent<Tag>("logo_production_glow");
    prodGlow->addComponent<Script>(productionGlowScript);
    
}

/**
 * @brief Create Kayu logo animation with exponential slam effect
 */
void Creator::createKayu()
{
    auto window = _world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 3.0f;

    auto kayu = _world.createEntity();
    kayu->addComponent<Scene>(11);
    kayu->addComponent<Layer>(2);
    kayu->addComponent<Tag>("logo_kayu");
    kayu->addComponent<Velocity>(10.f, 0.f);
    kayu->addComponent<SoundEffect>("../assets/sounds/kayu.mp3", 100.f);
    kayu->addComponent<Text>("KAYU", "../assets/font/title.ttf", 120);
    kayu->addComponent<Position>(-8000.f, centerY);
    kayu->addComponent<Script>(kayuScript);

    auto kayuGlow = _world.createEntity();
    kayuGlow->addComponent<Scene>(11);
    kayuGlow->addComponent<Layer>(1);
    kayuGlow->addComponent<Position>(kayu->getComponent<Position>()->getX(), centerY);
    kayuGlow->addComponent<Text>("KAYU", "../assets/font/title.ttf", 120);
    kayuGlow->addComponent<Tag>("logo_kayu_glow");
    kayuGlow->addComponent<Script>(kayuGlowScript);

    auto corp = _world.createEntity();
    corp->addComponent<Scene>(11);
    corp->addComponent<Layer>(2);
    corp->addComponent<Tag>("logo_corp");
    corp->addComponent<Position>(10000.f, centerY);
    corp->addComponent<Velocity>(-10.f, 0.f);
    corp->addComponent<Text>("CORP", "../assets/font/title.ttf", 120);
    corp->addComponent<Script>(corpScript);

    auto corpGlow = _world.createEntity();
    corpGlow->addComponent<Scene>(11);
    corpGlow->addComponent<Layer>(1);
    corpGlow->addComponent<Position>(corp->getComponent<Position>()->getX(), centerY);
    corpGlow->addComponent<Text>("CORP", "../assets/font/title.ttf", 120);
    corpGlow->addComponent<Tag>("logo_corp_glow");
    corpGlow->addComponent<Script>(corpGlowScript);
    
    auto dot = _world.createEntity();
    dot->addComponent<Scene>(11);
    dot->addComponent<Layer>(3);
    dot->addComponent<Tag>("logo_dot");
    dot->addComponent<Position>(centerX, centerY);
    dot->addComponent<RectangleShape>(200.f, 200.f, 255, 255, 255, 255);
    dot->addComponent<SoundEffect>("../assets/sounds/dot.mp3", 100.f);
    dot->addComponent<Script>(dotScript);
}

/**
 * @brief Create a Main Menu with TGUI
 */
void Creator::createTguiMenu()
{
    auto window = _world.getWindow();
    unsigned int width = window->getSize().x;
    float centerX = static_cast<float>(width) / 2.0f;

    auto music = _world.createEntity();
    music->addComponent<Music>("../assets/sounds/menu.mp3", 100.f, true);
    music->addComponent<Scene>(2);
    music->addComponent<Tag>("menu_music");

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

    auto btnPlay = _world.createEntity();
    btnPlay->addComponent<GuiWidget>(WidgetType::BUTTON, "START", menuRoot->getId());
    btnPlay->addComponent<Scene>(2);
    btnPlay->addComponent<Layer>(LayerType::UI + 1);
    btnPlay->addComponent<Tag>("menu_button_play");
    
    auto guiPlay = btnPlay->getComponent<GuiWidget>();
    styleNeonButton(guiPlay);
    guiPlay->setFont("../assets/font/title.ttf");
    guiPlay->setCallback([this]() {
        auto music = GameHelper::getEntityByTag(_world, "menu_music");
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
 * @brief Create an Options Menu with TGUI
 */
/**
 * @brief Create an Options Menu with a Scrollable area
 */
void Creator::createTguiOptions()
{
    auto optionsRoot = _world.createEntity();
    optionsRoot->addComponent<Scene>(3);
    optionsRoot->addComponent<Layer>(LayerType::UI);
    optionsRoot->addComponent<Position>(0.f, 0.f);
    optionsRoot->addComponent<GuiWidget>(WidgetType::PANEL);
    optionsRoot->addComponent<Tag>("options_root");
    auto rootGui = optionsRoot->getComponent<GuiWidget>();
    rootGui->setSize("100%", "100%");
    rootGui->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(10, 10, 30, 240));

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, "OPTIONS", optionsRoot->getId());
    titleEntity->addComponent<Scene>(3);
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    titleEntity->addComponent<Tag>("options_title");
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/title.ttf");
    guiTitle->setTextSize(80);
    guiTitle->setTextColor(sf::Color::Green);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "10%");

    auto scrollPanelEntity = _world.createEntity();
    scrollPanelEntity->addComponent<GuiWidget>(WidgetType::SCROLLABLE_PANEL, "", optionsRoot->getId());
    scrollPanelEntity->addComponent<Scene>(3);
    scrollPanelEntity->addComponent<Layer>(LayerType::UI + 1);
    scrollPanelEntity->addComponent<Tag>("options_scroll_panel");
    auto guiScroll = scrollPanelEntity->getComponent<GuiWidget>();
    guiScroll->setSize("70%", "60%");
    guiScroll->setPosition("50%", "50%");
    guiScroll->setOrigin(0.5f, 0.5f);
    
    auto scrollRender = guiScroll->getRawWidget()->getRenderer();
    scrollRender->setProperty("ScrollbarWidth", 10);
    scrollRender->setProperty("BackgroundColor", tgui::Color(20, 20, 40, 200));
    scrollRender->setProperty("BorderColor", tgui::Color::Cyan);
    scrollRender->setProperty("Borders", tgui::Borders(2));
    scrollRender->setProperty("RoundedBorderRadius", 10);

    auto mainLayoutEntity = _world.createEntity();
    mainLayoutEntity->addComponent<GuiWidget>(WidgetType::VERTICAL_LAYOUT, "", scrollPanelEntity->getId());
    mainLayoutEntity->addComponent<Scene>(3);
    mainLayoutEntity->addComponent<Tag>("options_main_layout");
    auto guiLayout = mainLayoutEntity->getComponent<GuiWidget>();
    guiLayout->setSize("100%", "150%");
    
    auto createOptionToggle = [this, mainLayoutEntity](const std::string& label, bool& stateValue) {
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(3);
        rowEntity->addComponent<Tag>("option_toggle_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "5%");
        styleNeonRow(guiRow);

        auto btnEntity = _world.createEntity();
        btnEntity->addComponent<GuiWidget>(WidgetType::BUTTON, label, rowEntity->getId());
        btnEntity->addComponent<Scene>(3);
        btnEntity->addComponent<Tag>("option_toggle_button");
        auto guiBtn = btnEntity->getComponent<GuiWidget>();
        guiBtn->setSize("50%", "70%");
        guiBtn->setOrigin(0.5f, 0.5f);
        guiBtn->setPosition("30%", "50%");
        guiBtn->setFont("../assets/font/title.ttf");
        styleNeonButton(guiBtn);

        auto statusEntity = _world.createEntity();
        statusEntity->addComponent<GuiWidget>(WidgetType::LABEL, stateValue ? "ON" : "OFF", rowEntity->getId());
        statusEntity->addComponent<Scene>(3);
        statusEntity->addComponent<Tag>("option_toggle_status");
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

    auto createOptionSlider = [this, mainLayoutEntity](const std::string& label, float initialValue, std::function<void(float)> onValueChange) {
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(3);
        rowEntity->addComponent<Tag>("option_slider_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "100");
        styleNeonRow(guiRow);

        auto labelEntity = _world.createEntity();
        labelEntity->addComponent<GuiWidget>(WidgetType::LABEL, label, rowEntity->getId());
        labelEntity->addComponent<Scene>(3);
        labelEntity->addComponent<Tag>("option_slider_label");
        auto guiLabel = labelEntity->getComponent<GuiWidget>();
        guiLabel->setTextSize(25);
        guiLabel->setPosition("10%", "50%");
        guiLabel->setOrigin(0.f, 0.5f);
        guiLabel->setTextColor(sf::Color::White);

        auto sliderEntity = _world.createEntity();
        sliderEntity->addComponent<GuiWidget>(WidgetType::SLIDER, "", rowEntity->getId());
        sliderEntity->addComponent<Scene>(3);
        sliderEntity->addComponent<Tag>("option_slider");
        auto guiSlider = sliderEntity->getComponent<GuiWidget>();
        guiSlider->setSize("40%", "20");
        guiSlider->setPosition("70%", "50%");
        guiSlider->setOrigin(0.5f, 0.5f);
        guiSlider->setRange(0, 100);
        guiSlider->setValue(initialValue);
        styleNeonSlider(guiSlider);

        auto rawSlider = std::dynamic_pointer_cast<tgui::Slider>(guiSlider->getRawWidget());
        if (rawSlider) {
            rawSlider->onValueChange(onValueChange);
        }
    };

    static bool dummy = false;
    createOptionToggle("GOD MODE", dummy);
    createOptionToggle("EASY MODE", dummy);
    createOptionToggle("HARD MODE", dummy);
    createOptionToggle("ONE HIT KILL", dummy);

    auto btnReturn = _world.createEntity();
    btnReturn->addComponent<GuiWidget>(WidgetType::BUTTON, "BACK", optionsRoot->getId());
    btnReturn->addComponent<Scene>(3);
    btnReturn->addComponent<Layer>(LayerType::UI + 2);
    auto guiReturn = btnReturn->getComponent<GuiWidget>();
    guiReturn->setSize(200, 60);
    guiReturn->setOrigin(0.5f, 0.5f);
    guiReturn->setPosition("50%", "85%");
    guiReturn->setCallback([this]() { _world.setCurrentScene(2); });
    styleNeonButton(guiReturn);
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
        {"is_hard_mode", "false"},
        {"mana", "100"}
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

    auto hpBarRed = _world.createEntity();
    hpBarRed->addComponent<RectangleShape>(400.f, 20.f, 150, 0, 0, 200);
    hpBarRed->addComponent<Position>(20.f, 20.f + (playerCount - 1) * 30.f);
    hpBarRed->addComponent<Layer>(LayerType::UI);
    hpBarRed->addComponent<Scene>(1);
    hpBarRed->addComponent<Tag>("hp_bar_red_" + std::to_string(playerCount));
    hpBarRed->addComponent<Group>(playerCount);

    auto hpBarGreen = _world.createEntity();
    hpBarGreen->addComponent<RectangleShape>(400.f, 20.f, 0, 200, 0, 200);
    hpBarGreen->addComponent<Position>(21.f, 21.f + (playerCount - 1) * 30.f);
    hpBarGreen->addComponent<Layer>(LayerType::UI + 1);
    hpBarGreen->addComponent<Scene>(1);
    hpBarGreen->addComponent<Tag>("hp_bar_green_" + std::to_string(playerCount));
    hpBarGreen->addComponent<Group>(playerCount);
    hpBarGreen->addComponent<Script>(hpBarScript);

    auto manaBarEmpty = _world.createEntity();
    manaBarEmpty->addComponent<RectangleShape>(400.f, 10.f, 150, 150, 255, 200);
    manaBarEmpty->addComponent<Position>(20.f, 45.f + (playerCount - 1) * 30.f);
    manaBarEmpty->addComponent<Layer>(LayerType::UI);
    manaBarEmpty->addComponent<Scene>(1);
    manaBarEmpty->addComponent<Tag>("mana_bar_empty_" + std::to_string(playerCount));
    manaBarEmpty->addComponent<Group>(playerCount);

    auto manaBar = _world.createEntity();
    manaBar->addComponent<RectangleShape>(400.f, 10.f, 0, 0, 255, 200);
    manaBar->addComponent<Position>(21.f, 46.f + (playerCount - 1) * 30.f);
    manaBar->addComponent<Layer>(LayerType::UI + 1);
    manaBar->addComponent<Scene>(1);
    manaBar->addComponent<Tag>("mana_bar_full_" + std::to_string(playerCount));
    manaBar->addComponent<Group>(playerCount);
    manaBar->addComponent<Script>(manaBarScript);
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
    status->getComponent<Text>()->setColor(200, 200, 200, 255);
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

/**
 * @brief Create spark effects at a given position.
 * 
 * This function generates spark entities with random velocities.
 * @param world The game world where the sparks will be created.
 * @param x The x-coordinate for the spark origin.
 * @param y The y-coordinate for the spark origin.
 * @param amount The number of sparks to create.
 */
void Creator::createSparks(World &world, float x, float y, int amount)
{
    for (int i = 0; i < amount; i++) {
        auto spark = world.createEntity();
        spark->addComponent<Scene>(11);
        spark->addComponent<Position>(x, y);
        float vx = (rand() % 200 - 100) / 10.f;
        float vy = (rand() % 200 - 100) / 10.f;
        spark->addComponent<Velocity>(vx, vy);
        spark->addComponent<RectangleShape>(4.f, 4.f, 255, 255, 255, 255);
        spark->getComponent<RectangleShape>()->setColor(255, 215, 0, 255);
        spark->addComponent<Script>([](int id, World& w) {
            auto e = GameHelper::getEntityById(w, id);
            if (!e) return;
            auto r = e->getComponent<RectangleShape>();
            if (r->getSize().x > 0.1f) {
                r->setSize(r->getSize().x * 0.9f, r->getSize().y * 0.9f);
                r->setColor(r->getColor().r, r->getColor().g * 0.9f, r->getColor().b, r->getColor().a);
            }
            else
                w.killEntity(id);
        });
    }
}