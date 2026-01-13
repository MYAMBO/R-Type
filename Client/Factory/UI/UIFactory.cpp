/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** UIFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "UIFactory.hpp"

#include <thread>

UIFactory::UIFactory(World& world) : _world(world), _languageHandler(std::make_shared<LanguageHandler>("en"))
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
void UIFactory::createLoadingScreen() const
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

void UIFactory::_addOptionToggle(const std::string& label, bool& stateValue, uint64_t parentId) const
{
    auto row = _world.createEntity();
    row->addComponent<GuiWidget>(WidgetType::PANEL, "", parentId);
    row->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    row->addComponent<Tag>("option_row");
    auto guiRow = row->getComponent<GuiWidget>();
    guiRow->setSize("100%", "100");
    styleNeonRow(guiRow);

    auto btn = _world.createEntity();
    btn->addComponent<Data>(std::map<std::string, std::string>{{"text", label}});
    btn->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btn->getComponent<Data>()->getData("text")), row->getId());
    btn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    btn->addComponent<Tag>("option_button");
    auto guiBtn = btn->getComponent<GuiWidget>();
    guiBtn->setSize("50%", "70%");
    guiBtn->setOrigin(0.5f, 0.5f);
    guiBtn->setPosition("30%", "50%");
    styleNeonButton(guiBtn);

    auto status = _world.createEntity();
    status->addComponent<GuiWidget>(WidgetType::LABEL, stateValue ? "ON" : "OFF", row->getId());
    status->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    status->addComponent<Tag>("option_status");
    auto guiStatus = status->getComponent<GuiWidget>();
    guiStatus->setTextSize(30);
    guiStatus->setOrigin(0.5f, 0.5f);
    guiStatus->setPosition("80%", "50%");
    guiStatus->setTextColor(stateValue ? sf::Color::Green : sf::Color::Red);

    guiBtn->setCallback([&stateValue, guiStatus]() {
        stateValue = !stateValue;
        guiStatus->setText(stateValue ? "ON" : "OFF");
        guiStatus->setTextColor(stateValue ? sf::Color::Green : sf::Color::Red);
    });
}

void UIFactory::_addColorBlindCycle(const std::string& label, uint64_t parentId) const
{
    auto row = _world.createEntity();
    row->addComponent<GuiWidget>(WidgetType::PANEL, "", parentId);
    row->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    row->addComponent<Tag>("option_row");
    auto guiRow = row->getComponent<GuiWidget>();
    guiRow->setSize("100%", "100");
    styleNeonRow(guiRow);

    auto btn = _world.createEntity();
    btn->addComponent<Data>(std::map<std::string, std::string>{{"text", label}});
    btn->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btn->getComponent<Data>()->getData("text")), row->getId());
    btn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    btn->addComponent<Tag>("option_button");
    auto guiBtn = btn->getComponent<GuiWidget>();
    guiBtn->setSize("50%", "70%");
    guiBtn->setOrigin(0.5f, 0.5f);
    guiBtn->setPosition("30%", "50%");
    styleNeonButton(guiBtn);

    std::string currentMode = "normal";
    auto settings = GameHelper::getEntityByTag(_world, "game_availability_settings");
    if (settings) {
        auto data = settings->getComponent<Data>();
        if (data && data->hasData("color_blind_mode")) {
            currentMode = data->getData("color_blind_mode");
        }
    }
    std::string displayInit = currentMode;
    std::transform(displayInit.begin(), displayInit.end(), displayInit.begin(), ::toupper);

    auto status = _world.createEntity();
    status->addComponent<GuiWidget>(WidgetType::LABEL, displayInit, row->getId());
    status->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    status->addComponent<Tag>("option_status");
    auto guiStatus = status->getComponent<GuiWidget>();
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
        int nextIdx = (it != modes.end()) ? (std::distance(modes.begin(), it) + 1) % modes.size() : 0;
        
        std::string nextMode = modes[nextIdx];
        data->setData("color_blind_mode", nextMode);
        
        std::string display = nextMode;
        std::transform(display.begin(), display.end(), display.begin(), ::toupper);
        guiStatus->setText(display);
    });
}

void UIFactory::_addOptionSlider(const std::string& label, float initialValue, uint64_t parentId, std::function<void(float)> onValueChange, std::function<void(int, World&)> onUpdate) const
{
    auto row = _world.createEntity();
    row->addComponent<GuiWidget>(WidgetType::PANEL, "", parentId);
    row->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    row->addComponent<Tag>("option_row");
    auto guiRow = row->getComponent<GuiWidget>();
    guiRow->setSize("100%", "100");
    styleNeonRow(guiRow);

    auto guiLabel = _world.createEntity();
    guiLabel->addComponent<Data>(std::map<std::string, std::string>{{"text", label}});
    guiLabel->addComponent<GuiWidget>(WidgetType::LABEL, _languageHandler->getTranslation(guiLabel->getComponent<Data>()->getData("text")), row->getId());
    guiLabel->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    guiLabel->addComponent<Tag>("option_label");
    auto gl = guiLabel->getComponent<GuiWidget>();
    gl->setTextSize(25);
    gl->setPosition("10%", "50%");
    gl->setOrigin(0.f, 0.5f);
    gl->setTextColor(sf::Color::White);

    auto slider = _world.createEntity();
    slider->addComponent<GuiWidget>(WidgetType::SLIDER, "", row->getId());
    slider->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    slider->addComponent<Tag>("option_slider");
    if (onUpdate) slider->addComponent<Script>(onUpdate);
    auto gs = slider->getComponent<GuiWidget>();
    gs->setSize("40%", "20");
    gs->setPosition("70%", "50%");
    gs->setOrigin(0.5f, 0.5f);
    gs->setRange(0, 100);
    gs->setValue(initialValue);
    styleNeonSlider(gs);

    auto raw = std::dynamic_pointer_cast<tgui::Slider>(gs->getRawWidget());
    if (raw) raw->onValueChange(onValueChange);
}

void UIFactory::_addKeyBindingRow(const std::string& actionName, uint64_t parentId) const
{
    auto row = _world.createEntity();
    row->addComponent<GuiWidget>(WidgetType::PANEL, "", parentId);
    row->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    row->addComponent<Tag>("keybinding_row");
    auto guiRow = row->getComponent<GuiWidget>();
    guiRow->setSize("100%", "100");
    styleNeonRow(guiRow);

    auto lbl = _world.createEntity();
    lbl->addComponent<GuiWidget>(WidgetType::LABEL, actionName, row->getId());
    lbl->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    lbl->addComponent<Tag>("keybinding_label");
    auto gl = lbl->getComponent<GuiWidget>();
    gl->setTextSize(25);
    gl->setPosition("10%", "50%");
    gl->setOrigin(0.f, 0.5f);
    gl->setTextColor(sf::Color::White);

    auto btn = _world.createEntity();
    btn->addComponent<GuiWidget>(WidgetType::BUTTON, "", row->getId());
    btn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    btn->addComponent<Tag>("keybinding_button");
    auto guiBtn = btn->getComponent<GuiWidget>();
    styleNeonButton(guiBtn);
    guiBtn->setSize("40%", "70%");
    guiBtn->setPosition("70%", "50%");
    guiBtn->setOrigin(0.5f, 0.5f);

    auto settings = GameHelper::getEntityByTag(_world, "game_controls_settings");
    if (settings) guiBtn->setText(settings->getComponent<Data>()->getData(actionName));

    guiBtn->setCallback([this, guiBtn, actionName]() {
        guiBtn->setText("...");
        auto listener = _world.createEntity();
        listener->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        listener->addComponent<Tag>("keybinding_listener");
        listener->addComponent<Script>([guiBtn, actionName](int id, World& w) {
            auto input = w.getSystem<Inputs>();
            if (!input) return;
            KeyboardKey key = input->consumeLastKey();
            if (key != KeyboardKey::Key_Unknown) {
                std::string name = input->keyToString(key);
                auto s = GameHelper::getEntityByTag(w, "game_controls_settings");
                if (s) s->getComponent<Data>()->setData(actionName, name);
                guiBtn->setText(name);
                w.killEntity(id);
            }
        });
    });
}

/**
 * @brief Create an Options Menu with Tabs (Scene 3)
 */
void UIFactory::createOptionsMenu() const
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
    titleEntity->addComponent<Data>(std::map<std::string, std::string>{{"text", "SETTINGS"}});
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, _languageHandler->getTranslation(titleEntity->getComponent<Data>()->getData("text")), optionsRoot->getId());
    titleEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    titleEntity->addComponent<Tag>("options_title");
    auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/regular.ttf");
    guiTitle->setTextSize(60);
    guiTitle->setTextColor(sf::Color::Green);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "8%");

    auto tabHeaderEntity = _world.createEntity();
    tabHeaderEntity->addComponent<GuiWidget>(WidgetType::HORIZONTAL_LAYOUT, "", optionsRoot->getId());
    tabHeaderEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    tabHeaderEntity->addComponent<Tag>("options_tab_header");
    auto guiTabHeader = tabHeaderEntity->getComponent<GuiWidget>();
    guiTabHeader->setSize("60%", "50");
    guiTabHeader->setPosition("50%", "18%");
    guiTabHeader->setOrigin(0.5f, 0.5f);

    auto scrollPanelEntity = _world.createEntity();
    scrollPanelEntity->addComponent<GuiWidget>(WidgetType::SCROLLABLE_PANEL, "", optionsRoot->getId());
    scrollPanelEntity->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    scrollPanelEntity->addComponent<Tag>("options_scroll_panel");
    auto guiScroll = scrollPanelEntity->getComponent<GuiWidget>();
    guiScroll->setSize("70%", "55%");
    guiScroll->setPosition("50%", "55%");
    guiScroll->setOrigin(0.5f, 0.5f);
    auto scrollRender = guiScroll->getRawWidget()->getRenderer();
    scrollRender->setProperty("ScrollbarWidth", 10);
    scrollRender->setProperty("BackgroundColor", tgui::Color(20, 20, 40, 255));
    scrollRender->setProperty("BorderColor", tgui::Color::Cyan);
    scrollRender->setProperty("Borders", tgui::Borders(2));
    scrollRender->setProperty("RoundedBorderRadius", 10);

    auto createCategory = [this, scrollPanelEntity](const std::string& tag, bool visible) {
        auto cat = _world.createEntity();
        cat->addComponent<GuiWidget>(WidgetType::VERTICAL_LAYOUT, "", scrollPanelEntity->getId());
        cat->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        cat->addComponent<Tag>(tag);
        auto gui = cat->getComponent<GuiWidget>();
        gui->setSize("100%", "200%");
        gui->setVisible(visible);
        return cat->getId();
    };

    uint64_t layoutGeneralId = createCategory("options_layout_general", true);
    uint64_t layoutAudioId = createCategory("options_layout_audio", false);
    uint64_t layoutGameplayId = createCategory("options_layout_gameplay", false);

    auto addTabButton = [this, tabHeaderEntity, layoutGeneralId, layoutAudioId, layoutGameplayId]
                        (const std::string& label, uint64_t targetId) {
        auto btn = _world.createEntity();
        btn->addComponent<GuiWidget>(WidgetType::BUTTON, label, tabHeaderEntity->getId());
        btn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
        btn->addComponent<Tag>("options_tab_button_" + label);
        auto gui = btn->getComponent<GuiWidget>();
        styleNeonButton(gui);
        gui->setCallback([this, targetId, layoutGeneralId, layoutAudioId, layoutGameplayId]() {
            GameHelper::getEntityById(_world, layoutGeneralId)->getComponent<GuiWidget>()->setVisible(false);
            GameHelper::getEntityById(_world, layoutAudioId)->getComponent<GuiWidget>()->setVisible(false);
            GameHelper::getEntityById(_world, layoutGameplayId)->getComponent<GuiWidget>()->setVisible(false);
            GameHelper::getEntityById(_world, targetId)->getComponent<GuiWidget>()->setVisible(true);
        });
    };

    addTabButton("GENERAL", layoutGeneralId);
    addTabButton("AUDIO", layoutAudioId);
    addTabButton("CONTROLS", layoutGameplayId);

    static bool godMode = false;
    static bool easyMode = false;
    static bool hardMode = false;

    auto entity = GameHelper::getEntityByTag(_world, "game_availability_settings");
    static bool dyslexiaMode = false;
    if (entity) {
        auto data = entity->getComponent<Data>();
        std::string dyslexiaStr = data->getData("disclexia_mode");
        if (dyslexiaStr == "true")
            dyslexiaMode = true;
    }

    _addColorBlindCycle("SETTINGS_COLOR_BLIND_MODE", layoutGeneralId);

    _addOptionToggle("SETTINGS_GOD_MODE", godMode, layoutGeneralId);
    _addOptionToggle("SETTINGS_EASY_MODE", easyMode, layoutGeneralId);
    _addOptionToggle("SETTINGS_HARD_MODE", hardMode, layoutGeneralId);
    _addOptionToggle("SETTINGS_DISLEXIA_MODE", dyslexiaMode, layoutGeneralId);

    auto entityVolume = GameHelper::getEntityByTag(_world, "game_volume_settings");
    float musicVolume = 100.f;
    float sfxVolume = 100.f;
    float masterVolume = 100.f;
    if (entityVolume) {
        auto data = entityVolume->getComponent<Data>();
        musicVolume = std::stof(data->getData("music_volume"));
        sfxVolume = std::stof(data->getData("sfx_volume"));
        masterVolume = std::stof(data->getData("master_volume"));
    }

    _addOptionSlider("SETTINGS_MUSIC_VOLUME", musicVolume, layoutAudioId, [](float){}, [](int id, World& w) {
        auto raw = std::dynamic_pointer_cast<tgui::Slider>(GameHelper::getEntityById(w, id)->getComponent<GuiWidget>()->getRawWidget());
        auto settings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (settings) settings->getComponent<Data>()->setData("music_volume", std::to_string((int)raw->getValue()));
    });
    _addOptionSlider("SETTINGS_SFX_VOLUME", sfxVolume, layoutAudioId, [](float){}, [](int id, World& w) {
        auto raw = std::dynamic_pointer_cast<tgui::Slider>(GameHelper::getEntityById(w, id)->getComponent<GuiWidget>()->getRawWidget());
        auto settings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (settings) settings->getComponent<Data>()->setData("sfx_volume", std::to_string((int)raw->getValue()));
    });
    _addOptionSlider("SETTINGS_MASTER_VOLUME", masterVolume, layoutAudioId, [](float){}, [](int id, World& w) {
        auto raw = std::dynamic_pointer_cast<tgui::Slider>(GameHelper::getEntityById(w, id)->getComponent<GuiWidget>()->getRawWidget());
        auto settings = GameHelper::getEntityByTag(w, "game_volume_settings");
        if (settings) settings->getComponent<Data>()->setData("master_volume", std::to_string((int)raw->getValue()));
    });

    _addKeyBindingRow("UP", layoutGameplayId);
    _addKeyBindingRow("DOWN", layoutGameplayId);
    _addKeyBindingRow("LEFT", layoutGameplayId);
    _addKeyBindingRow("RIGHT", layoutGameplayId);
    _addKeyBindingRow("SHOOT", layoutGameplayId);

    auto btnReturn = _world.createEntity();
    btnReturn->addComponent<Data>(std::map<std::string, std::string>{{"text", "BACK"}});
    btnReturn->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btnReturn->getComponent<Data>()->getData("text")), optionsRoot->getId());
    btnReturn->addComponent<Scene>(static_cast<int>(SceneType::OPTIONS));
    btnReturn->addComponent<Tag>("options_button_return");
    btnReturn->addComponent<Layer>(LayerType::UI + 2);
    auto guiReturn = btnReturn->getComponent<GuiWidget>();
    styleNeonButton(guiReturn);
    guiReturn->setSize(200, 60);
    guiReturn->setOrigin(0.5f, 0.5f);
    guiReturn->setPosition("50%", "90%");
    guiReturn->setCallback([this]() { _world.setCurrentScene(static_cast<int>(SceneType::MENU)); });
}

/**
 * @brief Create a beautiful and clean Main Menu using TGUI wrapped in ECS
 */
void UIFactory::createMenu() const
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
    btnPlay->addComponent<Data>(std::map<std::string, std::string>{{"text", "START_GAME"}});
    btnPlay->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btnPlay->getComponent<Data>()->getData("text")), layoutEntity->getId());
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
    btnOptions->addComponent<Data>(std::map<std::string, std::string>{{"text", "SETTINGS"}});
    btnOptions->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btnOptions->getComponent<Data>()->getData("text")), layoutEntity->getId());
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

    const auto btnLangOptions = _world.createEntity();
    btnLangOptions->addComponent<GuiWidget>(WidgetType::BUTTON, "🌐", menuRoot->getId());
    btnLangOptions->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    btnLangOptions->addComponent<Tag>("menu_button_languages");
    btnLangOptions->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
    btnLangOptions->getComponent<SoundEffect>()->setGlobal(true);
    const auto guiLangOpt = btnLangOptions->getComponent<GuiWidget>();
    guiLangOpt->setSize("100", "100");
    guiLangOpt->setPosition("2%", "95%");
    guiLangOpt->setOrigin(0.f, 1.f);
    styleNeonButton(guiLangOpt);
    guiLangOpt->setFont("../assets/font/NotoEmoji.ttf");
    guiLangOpt->setTextSize(50);
    guiLangOpt->setCallback([this]() {
        if (const auto sfx = GameHelper::getEntityByTag(_world, "menu_button_languages")->getComponent<SoundEffect>())
            sfx->play();
        _world.setCurrentScene(static_cast<int>(SceneType::LANGUAGES));
    });
    createLangSelector();
    auto spaceEntity2 = _world.createEntity();
    spaceEntity2->addComponent<GuiWidget>(WidgetType::LABEL, "", layoutEntity->getId());
    spaceEntity2->addComponent<Scene>(static_cast<int>(SceneType::MENU));
    spaceEntity2->addComponent<Tag>("menu_button_space2");

    auto btnQuit = _world.createEntity();
    btnQuit->addComponent<Data>(std::map<std::string, std::string>{{"text", "QUIT_GAME"}});
    btnQuit->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(btnQuit->getComponent<Data>()->getData("text")), layoutEntity->getId());
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

/**
 * @brief Create a beautiful and clean language selection menu
 */
void UIFactory::createLangSelector() const
{
    const auto langRoot = _world.createEntity();
    langRoot->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
    langRoot->addComponent<Layer>(LayerType::UI);
    langRoot->addComponent<Position>(0.f, 0.f);
    langRoot->addComponent<GuiWidget>(WidgetType::PANEL);
    langRoot->addComponent<Tag>("lang_root");
    const auto rootGui = langRoot->getComponent<GuiWidget>();
    rootGui->setSize("100%", "100%");
    rootGui->getRawWidget()->getRenderer()->setProperty("BackgroundColor", tgui::Color(10, 10, 30, 240));

    const auto titleEntity = _world.createEntity();
    titleEntity->addComponent<Data>(std::map<std::string, std::string>{{"text", "SETTINGS_LANGUAGE"}});
    titleEntity->addComponent<GuiWidget>(WidgetType::LABEL, _languageHandler->getTranslation(titleEntity->getComponent<Data>()->getData("text")), langRoot->getId());
    titleEntity->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
    titleEntity->addComponent<Layer>(LayerType::UI + 1);
    titleEntity->addComponent<Tag>("lang_title");
    const auto guiTitle = titleEntity->getComponent<GuiWidget>();
    guiTitle->setFont("../assets/font/regular.ttf");
    guiTitle->setTextSize(80);
    guiTitle->setTextColor(sf::Color::Cyan);
    guiTitle->setOrigin(0.5f, 0.5f);
    guiTitle->setPosition("50%", "15%");

    const auto scrollEntity = _world.createEntity();
    scrollEntity->addComponent<GuiWidget>(WidgetType::SCROLLABLE_PANEL, "", langRoot->getId());
    scrollEntity->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
    scrollEntity->addComponent<Layer>(LayerType::UI + 1);
    scrollEntity->addComponent<Tag>("lang_scroll");
    const auto guiScroll = scrollEntity->getComponent<GuiWidget>();
    guiScroll->setSize("70%", "60%");
    guiScroll->setPosition("50%", "50%");
    guiScroll->setOrigin(0.5f, 0.5f);
    const auto scrollRender = guiScroll->getRawWidget()->getRenderer();
    scrollRender->setProperty("ScrollbarWidth", 10);
    scrollRender->setProperty("BackgroundColor", tgui::Color(20, 20, 40, 200));
    scrollRender->setProperty("BorderColor", tgui::Color::Cyan);
    scrollRender->setProperty("Borders", tgui::Borders(2));
    scrollRender->setProperty("RoundedBorderRadius", 10);

    const auto layoutEntity = _world.createEntity();
    layoutEntity->addComponent<GuiWidget>(WidgetType::VERTICAL_LAYOUT, "", scrollEntity->getId());
    layoutEntity->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
    layoutEntity->addComponent<Tag>("lang_layout");
    const auto guiLayout = layoutEntity->getComponent<GuiWidget>();
    guiLayout->setSize("100%", "150%");
    std::vector<std::pair<std::string, std::string>> languages = {
        {"ENGLISH", "en"},
        {"FRANCAIS", "fr"},
        {"ESPANOL", "es"},
        {"DEUTSCH", "de"}
    };
    for (const auto&[language, id] : languages) {
        const auto rowEntity = _world.createEntity();
        rowEntity->addComponent<GuiWidget>(WidgetType::PANEL, "", layoutEntity->getId());
        rowEntity->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
        rowEntity->addComponent<Tag>("lang_row_" + id);
        const auto guiRow = rowEntity->getComponent<GuiWidget>();
        guiRow->setSize("95%", "60");
        styleNeonRow(guiRow);

        const auto btnEntity = _world.createEntity();
        btnEntity->addComponent<GuiWidget>(WidgetType::BUTTON, language, rowEntity->getId());
        btnEntity->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
        btnEntity->addComponent<Tag>("lang_btn_" + id);
        btnEntity->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
        btnEntity->getComponent<SoundEffect>()->setGlobal(true);
        const auto guiBtn = btnEntity->getComponent<GuiWidget>();
        guiBtn->setFont("../assets/font/regular.ttf");
        guiBtn->setSize("90%", "70%");
        guiBtn->setOrigin(0.5f, 0.5f);
        guiBtn->setPosition("50%", "50%");
        styleNeonButton(guiBtn);
        guiBtn->setCallback([this, code = id]() {
            if (const auto sfx = GameHelper::getEntityByTag(_world, "lang_btn_" + code)->getComponent<SoundEffect>())
                sfx->play();
            if (const auto settings = GameHelper::getEntityByTag(_world, "game_availability_settings"))
                if (const auto data = settings->getComponent<Data>())
                    data->setData("language", code);
            _languageHandler->loadLanguageFile(code);
            auto entities = _world.getAllEntitiesWithComponent<Data>();
            for (const auto& entity : entities)
                if (const auto dataComp = entity->getComponent<Data>())
                    if (const auto textKey = dataComp->getData("text"); !textKey.empty())
                        if (const auto guiComp = entity->getComponent<GuiWidget>())
                            guiComp->setText(_languageHandler->getTranslation(textKey));
            _world.setCurrentScene(static_cast<int>(SceneType::MENU));
        });
    }

    const auto backBtn = _world.createEntity();
    backBtn->addComponent<Data>(std::map<std::string, std::string>{{"text", "BACK"}});
    backBtn->addComponent<GuiWidget>(WidgetType::BUTTON, _languageHandler->getTranslation(backBtn->getComponent<Data>()->getData("text")), langRoot->getId());
    backBtn->addComponent<Scene>(static_cast<int>(SceneType::LANGUAGES));
    backBtn->addComponent<Layer>(LayerType::UI + 2);
    backBtn->addComponent<Tag>("lang_back_btn");
    backBtn->addComponent<SoundEffect>("../assets/sounds/clics.mp3", 100.f);
    backBtn->getComponent<SoundEffect>()->setGlobal(true);
    const auto guiBack = backBtn->getComponent<GuiWidget>();
    guiBack->setSize(200, 60);
    guiBack->setOrigin(0.5f, 0.5f);
    guiBack->setPosition("50%", "85%");
    guiBack->setFont("../assets/font/regular.ttf");
    styleNeonButton(guiBack);
    guiBack->setCallback([this]() {
        if (const auto sfx = GameHelper::getEntityByTag(_world, "lang_back_btn")->getComponent<SoundEffect>())
            sfx->play();
        _world.setCurrentScene(static_cast<int>(SceneType::MENU));
    });
}