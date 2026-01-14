/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** EffectFactory
*/

#include "Game.hpp"
#include "Factory.hpp"
#include "EffectFactory.hpp"

EffectFactory::EffectFactory(World& world) : _world(world)
{
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
void EffectFactory::createSparks(World &world, float x, float y, int amount)
{
    for (int i = 0; i < amount; i++) {
        auto spark = world.createEntity();
        spark->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
        spark->addComponent<Position>(x, y);
        float vx = (rand() % 200 - 100) / 10.f;
        float vy = (rand() % 200 - 100) / 10.f;
        spark->addComponent<Velocity>(vx, vy);
        spark->addComponent<RectangleShape>(4.f, 4.f, 255, 255, 255, 255);
        spark->getComponent<RectangleShape>()->setColor(255, 215, 0, 255);
        spark->addComponent<Script>(sparkScript);
    }
}

/**
 * @brief Create Myambo logo animation with production effect
 */
void EffectFactory::createMyambo()
{
    auto window = _world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    auto myambo = _world.createEntity();
    myambo->addComponent<Text>("MYAMBO", "../assets/font/logo.ttf", 10);
    myambo->getComponent<Text>()->setColor(255, 255, 255, 255);
    myambo->addComponent<Scene>(static_cast<int>(SceneType::MYAMBO));
    myambo->addComponent<Layer>(2);
    myambo->addComponent<Tag>("logo_myambo");
    myambo->addComponent<SoundEffect>("../assets/sounds/logo.mp3", 100.f);
    myambo->addComponent<Position>(centerX , centerY);

    auto myamboGlow = _world.createEntity();
    myamboGlow->addComponent<Scene>(static_cast<int>(SceneType::MYAMBO));
    myamboGlow->addComponent<Layer>(1);
    myamboGlow->addComponent<Position>(myambo->getComponent<Position>()->getX(), myambo->getComponent<Position>()->getY());
    myamboGlow->addComponent<Text>("MYAMBO", "../assets/font/logo.ttf", 10);
    myamboGlow->addComponent<Tag>("logo_myambo_glow");
    myamboGlow->addComponent<Script>(myamboGlowScript);
    myambo->addComponent<Script>(myamboScript);

    auto prod = _world.createEntity();
    prod->addComponent<Text>("PRODUCTION", "../assets/font/logo.ttf", 60);
    prod->getComponent<Text>()->setColor(0, 0, 0, 255);
    prod->getComponent<Text>()->setSize(60);
    prod->addComponent<Scene>(static_cast<int>(SceneType::MYAMBO));
    prod->addComponent<Layer>(2);
    prod->addComponent<Tag>("logo_production");
    prod->addComponent<SoundEffect>("../assets/sounds/production.mp3", 100.f);
    prod->addComponent<Position>(centerX , centerY + 220.f);
    std::map<std::string, std::string> dataMap = {{"displayed", "false"}};
    prod->addComponent<Data>(dataMap);
    prod->addComponent<Script>(productionScript);

    auto prodGlow = _world.createEntity();
    prodGlow->addComponent<Scene>(static_cast<int>(SceneType::MYAMBO));
    prodGlow->addComponent<Layer>(1);
    prodGlow->addComponent<Position>(prod->getComponent<Position>()->getX(), prod->getComponent<Position>()->getY());
    prodGlow->addComponent<Text>("PRODUCTION", "../assets/font/logo.ttf", 60);
    prodGlow->getComponent<Text>()->setColor(0, 0, 0, 255);
    prodGlow->addComponent<Tag>("logo_production_glow");
    prodGlow->addComponent<Script>(productionGlowScript);
    
}

/**
 * @brief Create Kayu logo animation with slam effect
 */
void EffectFactory::createKayu()
{
    auto window = _world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 3.0f;

    auto kayu = _world.createEntity();
    kayu->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
    kayu->addComponent<Layer>(2);
    kayu->addComponent<Tag>("logo_kayu");
    kayu->addComponent<Velocity>(10.f, 0.f);
    kayu->addComponent<SoundEffect>("../assets/sounds/kayu.mp3", 100.f);
    kayu->addComponent<Text>("KAYU", "../assets/font/logo.ttf", 120);
    kayu->addComponent<Position>(-8000.f, centerY);
    kayu->addComponent<Script>(kayuScript);

    auto kayuGlow = _world.createEntity();
    kayuGlow->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
    kayuGlow->addComponent<Layer>(1);
    kayuGlow->addComponent<Position>(kayu->getComponent<Position>()->getX(), centerY);
    kayuGlow->addComponent<Text>("KAYU", "../assets/font/logo.ttf", 120);
    kayuGlow->addComponent<Tag>("logo_kayu_glow");
    kayuGlow->addComponent<Script>(kayuGlowScript);

    auto corp = _world.createEntity();
    corp->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
    corp->addComponent<Layer>(2);
    corp->addComponent<Tag>("logo_corp");
    corp->addComponent<Position>(10000.f, centerY);
    corp->addComponent<Velocity>(-10.f, 0.f);
    corp->addComponent<Text>("CORP", "../assets/font/logo.ttf", 120);
    corp->addComponent<Script>(corpScript);

    auto corpGlow = _world.createEntity();
    corpGlow->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
    corpGlow->addComponent<Layer>(1);
    corpGlow->addComponent<Position>(corp->getComponent<Position>()->getX(), centerY);
    corpGlow->addComponent<Text>("CORP", "../assets/font/logo.ttf", 120);
    corpGlow->addComponent<Tag>("logo_corp_glow");
    corpGlow->addComponent<Script>(corpGlowScript);
    
    auto dot = _world.createEntity();
    dot->addComponent<Scene>(static_cast<int>(SceneType::KAYU));
    dot->addComponent<Layer>(3);
    dot->addComponent<Tag>("logo_dot");
    dot->addComponent<Position>(centerX, centerY);
    dot->addComponent<RectangleShape>(200.f, 200.f, 255, 255, 255, 255);
    dot->addComponent<SoundEffect>("../assets/sounds/dot.mp3", 100.f);
    dot->addComponent<Script>(dotScript);
}

/**
 * @brief Create a scrolling credits screen
 */
void EffectFactory::createCredits()
{
    auto window = _world.getWindow();
    float width = static_cast<float>(window->getSize().x);
    float height = static_cast<float>(window->getSize().y);
    float centerX = width / 8.f;
    float centerX2 = width / 2.f;

    std::vector<std::pair<std::string, std::string>> credits = {
        {"A Cinematic Experience by", "MYAMBO STUDIOS"},
        {"In Strategic Alliance with", "KAYU CORP"},
        {"", ""},
        {"--- DIRECTION & PRODUCTION ---", ""},
        {"Chief Executive Producer", "Antoine"},
        {"Global Creative Director", "Martin"},
        {"Lead Technical Supervisor", "Pierre"},
        {"Head of Production Logic", "Yanis"},
        {"Operations Strategy Manager", "Timote"},
        {"", ""},
        {"--- SOFTWARE ENGINEERING ---", ""},
        {"Core Engine Architect", "Pierre"},
        {"Low-Level Systems Specialist", "Martin"},
        {"Memory Management Lead", "Pierre"},
        {"Logic & Mathematics Analyst", "Yanis"},
        {"Scripting Pipeline Engineer", "Antoine"},
        {"", ""},
        {"--- NETWORK ARCHITECTURE ---", ""},
        {"Network Infrastructure Lead", "Antoine"},
        {"Synchronous State Strategist", "Timote"},
        {"Packet Loss Mitigation Expert", "Yanis"},
        {"UDP Protocol Ambassador", "Antoine"},
        {"", ""},
        {"--- VISUAL DESIGN ---", ""},
        {"Lead UI & UX Designer", "Martin"},
        {"Senior Animator (Sprite Work)", "Pierre"},
        {"Cinematic Lighting & Glow", "Martin"},
        {"Background Parallax Engineer", "Pierre"},
        {"", ""},
        {"--- AUDIO & MUSIC ---", ""},
        {"Director of Soundscapes", "Martin"},
        {"Lead Orchestral Composer", "Martin"},
        {"Atmospheric Silence Expert", "Martin"},
        {"", ""},
        {"--- COMPILATION TEAM ---", ""},
        {"Senior Segfault Investigator", "Yanis"},
        {"Junior Pointer Mismanager", "Timote"},
        {"Memory Leak Denial Liaison", "Pierre"},
        {"Git Conflict Crisis Manager", "Antoine"},
        {"", ""},
        {"--- LOGISTIC DEPARTMENT ---", ""},
        {"Chief Caffeine Procurement", "Timote"},
        {"Snack Distribution Coordinator", "Martin"},
        {"Rubber Duck Conversations", "Pierre"},
        {"Head of Keyboard Sanitation", "Martin"},
        {"Emergency Nap Coordinator", "Antoine"},
        {"", ""},
        {"--- COMPLAINTS BUREAU ---", ""},
        {"Professional Bug Apologist", "Antoine"},
        {"'It Worked On My Machine' Officer", "Martin"},
        {"Feature-to-Bug Translator", "Timote"},
        {"Senior Shrug Expert", "Pierre"},
        {"", ""},
        {"--- SPIRITUAL DEPARTMENT ---", ""},
        {"Supreme Divine Inspiration", "Yae Miko"},
        {"Mental Health (What's that?)", "Our Compiler"},
        {"", ""},
        {"--- SPECIAL THANKS ---", ""},
        {"The Guy who invented Ctrl+C", "The Real MVP"},
        {"StackOverflow Thread #48291", "For the save"},
        {"ChatGPT", "For writing this list"},
        {"", ""},
        {"--- DEVELOPMENT STATISTICS ---", ""},
        {"Keyboards Destroyed", "3"},
        {"Liters of Coffee Consumed", "237"},
        {"Hours of Sleep Lost", "Infinity"},
        {"Lines of Code Deleted", "More than kept"},
        {"Merge Conflicts Resolved", "842 (mostly by crying)"},
        {"Times 'It works on my PC' was said", "154"},
        {"Energy Drink Cans Under the Desk", "1,294"},
        {"Hours spent rubber ducking", "42"},
        {"Rubber Ducks that quit their job", "2"},
        {"Features originally reported as bugs", "34"},
        {"Git commits named just 'fix'", "1,023"},
        {"Git commits named 'final fix'", "87"},
        {"Git commits named 'AAAAAAAHHHHHH'", "12"},
        {"Sunlight exposure (last 3 months)", "0.002 seconds"},
        {"Brain cells lost per Segfault", "1,500"},
        {"Times we thought about using Java", "0 (Never.)"},
        {"Remaining sanity", "Not found (404)"},
        {"", ""},
        {"--- DISCLAIMER ---", ""},
        {"No Segfaults were harmed", "Actually, many died."},
        {"This game was made by", "5 Humans & 1 Fox."},
        {"", ""},
        {"--- THE LEGENDARY FIVE ---", ""},
        {"ANTOINE", "The Ping"},
        {"MARTIN", "The Glow"},
        {"YANIS", "The Logic"},
        {"PIERRE", "The Engine"},
        {"TIMOTE", "The Packet"},
        {"", ""},
        {"THANK YOU FOR WATCHING", "PLEASE REBOOT YOUR COMPUTER NOW"}
    };

    auto music = _world.createEntity();
    music->addComponent<Music>("../assets/sounds/credits.mp3", 50.f, true);
    music->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
    music->addComponent<Tag>("credits_music");
    music->addComponent<Script>([](int id, World& w) {
        auto entity = GameHelper::getEntityById(w, id);
        auto sceneComp = entity->getComponent<Scene>();
        if (w.getCurrentScene() != sceneComp->getScene()) {
            auto musicComp = entity->getComponent<Music>();
            if (musicComp && musicComp->getState() != MusicState::STOPPED)
                musicComp->stop();
            return;
        }
        if (!entity)
            return;
        auto musicComp = entity->getComponent<Music>();
        if (musicComp && musicComp->getState() != MusicState::PLAYING) {
            musicComp->play();
        }
    });

    auto background = _world.createEntity();
    background->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
    background->addComponent<Layer>(LayerType::BACKGROUND + 1);
    background->addComponent<Tag>("credits_background");
    background->addComponent<RectangleShape>(width * 3, height * 3, 0, 0, 0, 255);
    background->addComponent<Position>(0.f, 0.f);

    float startY = height + 50.f;
    float lineSpacing = 80.f;

    auto title = _world.createEntity();
    title->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
    title->addComponent<Layer>(LayerType::UI);
    title->addComponent<Tag>("credits_title");
    title->addComponent<Position>(centerX + centerX / 2.f, startY - lineSpacing * 2);
    title->addComponent<Velocity>(0.f, -3.f);
    title->addComponent<Text>("CREDITS R-TYPE", "../assets/font/logo.ttf", 80);
    title->getComponent<Text>()->setColor(255, 255, 255, 255);

    auto subtitle = _world.createEntity();
    subtitle->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
    subtitle->addComponent<Layer>(LayerType::UI);
    subtitle->addComponent<Tag>("credits_subtitle");
    subtitle->addComponent<Position>(centerX + centerX / 2.f, startY - lineSpacing);
    subtitle->addComponent<Velocity>(0.f, -3.f);
    subtitle->addComponent<Text>("Thank you for playing!", "../assets/font/logo.ttf", 40);
    subtitle->getComponent<Text>()->setColor(255, 255, 255, 255);

    for (size_t i = 0; i < credits.size(); ++i) {
        if (!credits[i].first.empty())
        {
            auto role = _world.createEntity();
            role->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
            role->addComponent<Layer>(LayerType::UI);
            role->addComponent<Tag>("credit_role_" + std::to_string(i));
            role->addComponent<Position>(centerX, startY + (i * lineSpacing));
            role->addComponent<Velocity>(0.f, -3.f);
            role->addComponent<Script>(creditsScript);
            role->addComponent<Text>(credits[i].first, "../assets/font/logo.ttf", 20);
            auto txtRole = role->getComponent<Text>();
            txtRole->setColor(255, 255, 255, 180);
        }
        if (!credits[i].second.empty()) {
            auto name = _world.createEntity();
            name->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
            name->addComponent<Layer>(LayerType::UI);
            name->addComponent<Tag>("credit_name_" + std::to_string(i));
            name->addComponent<Position>(centerX2, startY + (i * lineSpacing));
            name->addComponent<Velocity>(0.f, -3.f);
            name->addComponent<Script>(creditsNameScript);
            name->addComponent<Text>(credits[i].second, "../assets/font/logo.ttf", 25);
            auto txtName = name->getComponent<Text>();
            txtName->setColor(255, 255, 255, 255);
        }
    }

    auto watcher = _world.createEntity();
    watcher->addComponent<Scene>(static_cast<int>(SceneType::CREDITS));
    watcher->addComponent<Tag>("credits_watcher");
    watcher->addComponent<Script>([](int id, World& w) {
        (void)id;
        if (w.getCurrentScene() != static_cast<int>(SceneType::CREDITS))
            return;
        auto inputs = w.getSystem<Inputs>();
        if (inputs && (inputs->isKeyPressed(KeyboardKey::Key_Escape) || inputs->isKeyPressed(KeyboardKey::Key_Space))) {
            w.setCurrentScene(2);
        }
    });
}
