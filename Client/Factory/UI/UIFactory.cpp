/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** UIFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "UIFactory.hpp"

UIFactory::UIFactory(World& world) : _world(world)
{
}

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
    gui->setTextSize(40); 
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


/**
 * @brief Creates the loading screen entities.
 *
 * This function initializes the loading screen with text and a progress bar.
 */
void UIFactory::createLoadingScreen()
{
    auto window = _world.getWindow();
    float centerX = window->getSize().x / 2.0f - 200.f;
    float centerY = window->getSize().y / 2.0f;

    auto status = _world.createEntity();
    status->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    status->addComponent<Text>("Initializing...", "../assets/font/regular.ttf", 20);
    status->addComponent<Position>(centerX - status->getComponent<Text>()->getGlobalBounds().size.x / 2.0f, centerY + 60.f);
    status->addComponent<Layer>(LayerType::UI);
    status->getComponent<Text>()->setColor(200, 200, 200, 255);
    status->addComponent<Tag>("loading_status");

    auto bgBar = _world.createEntity();
    bgBar->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    bgBar->addComponent<Position>(centerX - 200.f, centerY);
    bgBar->addComponent<RectangleShape>(400.f, 20.f, 50, 50, 50, 255);
    bgBar->addComponent<Tag>("loading_bg_bar");
    bgBar->addComponent<Scale>(1.f);
    bgBar->addComponent<Layer>(LayerType::UI);

    auto fillBar = _world.createEntity();
    fillBar->addComponent<Scene>(static_cast<int>(SceneType::LOADING));
    fillBar->addComponent<Position>(centerX - 200.f, centerY);
    fillBar->addComponent<RectangleShape>(1.f, 20.f, 100, 250, 50, 255);
    fillBar->addComponent<Layer>(LayerType::UI + 1);
    fillBar->addComponent<Tag>("loading_bar");
    fillBar->addComponent<Scale>(1.f);
}

/**
 * @brief Create an Options Menu with a Scrollable area
 */
void UIFactory::createOptionsMenu()
{
    auto optionsRoot = _world.createEntity();
    optionsRoot->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    optionsRoot->addComponent<Layer>(LayerType::UI);
    optionsRoot->addComponent<Position>(0.f, 0.f);
    optionsRoot->addComponent<GuiWidget>(WidgetType::PANEL);
    optionsRoot->addComponent<Tag>("options_root");
    auto rootGui = optionsRoot->getComponent<GuiWidget>();
    rootGui->setSize("100%", "100%");
    rootGui->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(10, 10, 30, 240));

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, "OPTIONS", optionsRoot->getId());
    titleEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    titleEntity->addComponent<Tag>("options_title");
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/regular.ttf");
    guiTitle->setTextSize(80);
    guiTitle->setTextColor(sf::Color::Green);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "10%");

    auto scrollPanelEntity = _world.createEntity();
    scrollPanelEntity->addComponent<GuiWidget>(WidgetType::SCROLLABLE_PANEL, "", optionsRoot->getId());
    scrollPanelEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
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
    mainLayoutEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    mainLayoutEntity->addComponent<Tag>("options_main_layout");
    auto guiLayout = mainLayoutEntity->getComponent<GuiWidget>();
    guiLayout->setSize("100%", "150%");
    
    auto createColorBlindCycle = [this, mainLayoutEntity](const std::string& label) {
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        rowEntity->addComponent<Tag>("color_blind_mode_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "100");
        styleNeonRow(guiRow);

        auto btnEntity = _world.createEntity();
        btnEntity->addComponent<GuiWidget>(WidgetType::BUTTON, label, rowEntity->getId());
        btnEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        btnEntity->addComponent<Tag>("color_blind_mode_button");
        auto guiBtn = btnEntity->getComponent<GuiWidget>();
        guiBtn->setSize("50%", "70%");
        guiBtn->setOrigin(0.5f, 0.5f);
        guiBtn->setPosition("30%", "50%");
        guiBtn->setFont("../assets/font/regular.ttf");
        styleNeonButton(guiBtn);

        auto statusEntity = _world.createEntity();
        statusEntity->addComponent<GuiWidget>(WidgetType::LABEL, "NORMAL", rowEntity->getId());
        statusEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        statusEntity->addComponent<Tag>("color_blind_mode_status");
        auto guiStatus = statusEntity->getComponent<GuiWidget>();
        guiStatus->setTextSize(20);
        guiStatus->setOrigin(0.5f, 0.5f);
        guiStatus->setPosition("80%", "50%");
        guiStatus->setTextColor(sf::Color::Cyan);
        guiBtn->setCallback([this, guiStatus]() {
            static std::vector<std::string> modes = {"protanopia", "deuteranopia", "tritanopia", "achromatopsia", "normal"};
            auto settings = GameHelper::getEntityByTag(_world, "game_availability_settings");
            if (!settings) return;
            auto data = settings->getComponent<Data>();
            std::string current = data->getData("color_blind_mode");
            auto it = std::find(modes.begin(), modes.end(), current);
            int nextIdx = 0;
            if (it != modes.end())
                nextIdx = (std::distance(modes.begin(), it) + 1) % modes.size();
            std::string nextMode = modes[nextIdx];
            data->setData("color_blind_mode", nextMode);
            std::string display = nextMode;
            std::transform(display.begin(), display.end(), display.begin(), ::toupper);
            guiStatus->setText(display);
        });
    };
    
    auto createOptionToggle = [this, mainLayoutEntity](const std::string& label, bool& stateValue) {
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        rowEntity->addComponent<Tag>("option_toggle_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "5%");
        styleNeonRow(guiRow);

        auto btnEntity = _world.createEntity();
        btnEntity->addComponent<GuiWidget>(WidgetType::BUTTON, label, rowEntity->getId());
        btnEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        btnEntity->addComponent<Tag>("option_toggle_button");
        auto guiBtn = btnEntity->getComponent<GuiWidget>();
        guiBtn->setSize("50%", "70%");
        guiBtn->setOrigin(0.5f, 0.5f);
        guiBtn->setPosition("30%", "50%");
        guiBtn->setFont("../assets/font/regular.ttf");
        styleNeonButton(guiBtn);

        auto statusEntity = _world.createEntity();
        statusEntity->addComponent<GuiWidget>(WidgetType::LABEL, stateValue ? "ON" : "OFF", rowEntity->getId());
        statusEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
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

    auto createOptionSlider = [this, mainLayoutEntity](const std::string& label, float initialValue, std::function<void(float)> onValueChange, std::function<void(int, World&)> onUpdate = nullptr) {
        auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", mainLayoutEntity->getId());
        rowEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        rowEntity->addComponent<Tag>("option_slider_row");
        auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("100%", "100");
        styleNeonRow(guiRow);

        auto labelEntity = _world.createEntity();
        labelEntity->addComponent<GuiWidget>(WidgetType::LABEL, label, rowEntity->getId());
        labelEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        labelEntity->addComponent<Tag>("option_slider_label");
        auto guiLabel = labelEntity->getComponent<GuiWidget>();
        guiLabel->setTextSize(25);
        guiLabel->setPosition("10%", "50%");
        guiLabel->setOrigin(0.f, 0.5f);
        guiLabel->setTextColor(sf::Color::White);

        auto sliderEntity = _world.createEntity();
        sliderEntity->addComponent<GuiWidget>(WidgetType::SLIDER, "", rowEntity->getId());
        sliderEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        sliderEntity->addComponent<Tag>("option_slider");
        if (onUpdate)
            sliderEntity->addComponent<Script>(onUpdate);
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

    static bool godMode = false;
    static bool easyMode = false;
    static bool hardMode = false;
    static bool disclexiaMode = false;
    createColorBlindCycle("COLORBLIND");
    createOptionToggle("GOD MODE", godMode);
    createOptionToggle("EASY MODE", easyMode);
    createOptionToggle("HARD MODE", hardMode);
    createOptionToggle("DISCLEXIA MODE", disclexiaMode);

    auto settingUpdater = _world.createEntity();
    settingUpdater->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    settingUpdater->addComponent<Tag>("options_setting_updater");
    settingUpdater->addComponent<Script>([&godMode, &easyMode, &hardMode, &disclexiaMode](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto dataEntity = GameHelper::getEntityByTag(w, "game_difficulty_settings");
        auto dataAvailability = GameHelper::getEntityByTag(w, "game_availability_settings");
        if (!dataEntity || !dataAvailability)
            return;
        auto dataComp = dataEntity->getComponent<Data>(); 
        if (dataComp) {
            dataComp->setData("god_mode", godMode ? "true" : "false");
            dataComp->setData("easy_mode", easyMode ? "true" : "false");
            dataComp->setData("hard_mode", hardMode ? "true" : "false");
        }
        auto dataCompAvail = dataAvailability->getComponent<Data>();
        if (dataCompAvail)
            dataCompAvail->setData("disclexia_mode", disclexiaMode ? "true" : "false");
    });

    createOptionSlider("MUSIC VOLUME", 100.f, [](float value) {(void)value;}, [](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto rawSlider = std::dynamic_pointer_cast<tgui::Slider>(entity->getComponent<GuiWidget>()->getRawWidget());
        if (!rawSlider)
            return;
        float value = static_cast<float>(rawSlider->getValue());
        auto volumeSettings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (volumeSettings) {
            volumeSettings->getComponent<Data>()->setData("music_volume", std::to_string(static_cast<int>(value)));
        }
    });
    createOptionSlider("SFX VOLUME", 100.f, [](float value) {(void)value;}, [](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto rawSlider = std::dynamic_pointer_cast<tgui::Slider>(entity->getComponent<GuiWidget>()->getRawWidget());
        if (!rawSlider)
            return;
        float value = static_cast<float>(rawSlider->getValue());
        auto volumeSettings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (volumeSettings) {
            volumeSettings->getComponent<Data>()->setData("sfx_volume", std::to_string(static_cast<int>(value)));
        }
    });
    createOptionSlider("MASTER VOLUME", 100.f, [](float value) {(void)value;}, [](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        if (!entity)
            return;
        auto rawSlider = std::dynamic_pointer_cast<tgui::Slider>(entity->getComponent<GuiWidget>()->getRawWidget());
        if (!rawSlider)
            return;
        float value = static_cast<float>(rawSlider->getValue());
        auto volumeSettings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (volumeSettings) {
            volumeSettings->getComponent<Data>()->setData("master_volume", std::to_string(static_cast<int>(value)));
        }
    });

    auto btnReturn = _world.createEntity();
    btnReturn->addComponent<GuiWidget>(WidgetType::BUTTON, "BACK", optionsRoot->getId());
    btnReturn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    btnReturn->addComponent<Layer>(LayerType::UI + 2);
    auto guiReturn = btnReturn->getComponent<GuiWidget>();
    guiReturn->setSize(200, 60);
    guiReturn->setOrigin(0.5f, 0.5f);
    guiReturn->setPosition("50%", "85%");
    guiReturn->setCallback([this]() { _world.setCurrentScene(static_cast<int>(SceneType::MENU)); });
    styleNeonButton(guiReturn);
}

/**
 * @brief Create a beautiful and clean Main Menu using TGUI wrapped in ECS
 */
void UIFactory::createMenu()
{
    auto music = _world.createEntity();
    music->addComponent<Music>("../assets/sounds/menu.mp3", 50.f, true);
    music->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    music->addComponent<Tag>("menu_music");
    music->getComponent<Music>()->play();
    music->addComponent<Script>([](int entityId, World& world) {
        auto entity = GameHelper::getEntityById(world, entityId);
        auto scene = world.getCurrentScene();
        if (!entity)
            return;
        if (scene == 2 || scene == 3) {
            auto musicComp = entity->getComponent<Music>();
            if (musicComp && musicComp->getState() != MusicState::PLAYING) {
                musicComp->play();
            }
        }
        else {
            auto musicComp = entity->getComponent<Music>();
            if (musicComp && musicComp->getState() == MusicState::PLAYING) {
                musicComp->stop();
            }
        }
    });

    auto menuRoot = _world.createEntity();
    menuRoot->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    menuRoot->addComponent<Layer>(LayerType::UI);
    menuRoot->addComponent<Tag>("menu_root");
    menuRoot->addComponent<Position>(0.f, 0.f);
    menuRoot->addComponent<GuiWidget>(WidgetType::PANEL);
    
    auto rootGui = menuRoot->getComponent<GuiWidget>();
    rootGui->setSize("100%", "100%");
    rootGui->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(5, 5, 15, 220));

    auto titleEntity = _world.createEntity();
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, "R-TYPE", menuRoot->getId());
    titleEntity->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    titleEntity->addComponent<Tag>("menu_title");
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/regular.ttf");
    guiTitle->setTextSize(120);
    guiTitle->setTextColor(sf::Color::Cyan);
    guiTitle->setTextStyle(tgui::TextStyle::Bold);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "20%");

    auto layoutEntity = _world.createEntity();
    layoutEntity->addComponent<GuiWidget>(WidgetType::VERTICAL_LAYOUT, "", menuRoot->getId());
    layoutEntity->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    layoutEntity->addComponent<Tag>("menu_button_layout");
    layoutEntity->addComponent<Layer>(LayerType::UI + 1);
    
    auto guiLayout = layoutEntity->getComponent<GuiWidget>();
    guiLayout->setSize("30%", "50%");
    guiLayout->setPosition("50%", "60%");
    guiLayout->setOrigin(0.5f, 0.5f);

    auto btnPlay = _world.createEntity();
    btnPlay->addComponent<GuiWidget>(WidgetType::BUTTON, "START MISSION", layoutEntity->getId());
    btnPlay->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    btnPlay->addComponent<Tag>("menu_button_start");
    btnPlay->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
    btnPlay->getComponent<SoundEffect>()->setGlobal(true);
    auto guiPlay = btnPlay->getComponent<GuiWidget>();
    styleNeonButton(guiPlay);
    guiPlay->setFont("../assets/font/regular.ttf");
    guiPlay->setCallback([this]() {
        auto sfx = GameHelper::getEntityByTag(_world, "menu_button_start")->getComponent<SoundEffect>();
        if (sfx)
            sfx->play();
        auto m = GameHelper::getEntityByTag(_world, "menu_music");
        if (m) m->getComponent<Music>()->stop();
        _world.setCurrentScene(static_cast<int>(SceneType::GAMEPLAY));
    });
    guiLayout->addSpace(0.2f);

    auto spaceEntity = _world.createEntity();
    spaceEntity->addComponent<GuiWidget>(WidgetType::LABEL, "", layoutEntity->getId());
    spaceEntity->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    spaceEntity->addComponent<Tag>("menu_button_space");

    auto btnOptions = _world.createEntity();
    btnOptions->addComponent<GuiWidget>(WidgetType::BUTTON, "SETTINGS", layoutEntity->getId());
    btnOptions->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    btnOptions->addComponent<Tag>("menu_button_options");
    btnOptions->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
    btnOptions->getComponent<SoundEffect>()->setGlobal(true);
    auto guiOpt = btnOptions->getComponent<GuiWidget>();
    styleNeonButton(guiOpt);
    guiOpt->setFont("../assets/font/regular.ttf");
    guiOpt->setCallback([this]() { 
        auto sfx = GameHelper::getEntityByTag(_world, "menu_button_options")->getComponent<SoundEffect>();
        if (sfx)
            sfx->play();
        _world.setCurrentScene(static_cast<int>(SceneType::OPTIONS));
    });
    auto spaceEntity2 = _world.createEntity();
    spaceEntity2->addComponent<GuiWidget>(WidgetType::LABEL, "", layoutEntity->getId());
    spaceEntity2->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    spaceEntity2->addComponent<Tag>("menu_button_space2");

    auto btnQuit = _world.createEntity();
    btnQuit->addComponent<GuiWidget>(WidgetType::BUTTON, "ABORT", layoutEntity->getId());
    btnQuit->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    btnQuit->addComponent<Tag>("menu_button_quit");
    btnQuit->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
    btnQuit->getComponent<SoundEffect>()->setGlobal(true);
    auto guiQuit = btnQuit->getComponent<GuiWidget>();
    styleNeonButton(guiQuit);
    guiQuit->setFont("../assets/font/regular.ttf");
    guiQuit->getRawWidget()->getRenderer()->setProperty("BorderColor", tgui::Color(255, 50, 50));
    guiQuit->getRawWidget()->getRenderer()->setProperty("TextColorHover", tgui::Color::Red);
    guiQuit->setCallback([this]() {
        auto sfx = GameHelper::getEntityByTag(_world, "menu_button_quit")->getComponent<SoundEffect>();
        if (sfx)
            sfx->play();
        if (_world.getWindow())
            _world.getWindow()->close();
    });

    createOptionsMenu();
}
