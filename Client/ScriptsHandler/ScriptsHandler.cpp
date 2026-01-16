/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ScriptsHandler
*/

#include "HP.hpp"
#include "Tag.hpp"
#include "Data.hpp"
#include "Text.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Group.hpp"
#include "Music.hpp"
#include "Inputs.hpp"
#include "Sprite.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Animator.hpp"
#include "GuiWidget.hpp"
#include "SoundEffect.hpp"
#include "RectangleShape.hpp"

#include "GameHelper.hpp"
#include "GameHelperGraphical.hpp"

#include "Network.hpp"
#include "Packet.hpp"

void backgroundScrollScript(size_t entityId, World &world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity) return;

    auto posComp = entity->getComponent<Position>();
    auto spriteComp = entity->getComponent<Sprite>();
    auto scaleComp = entity->getComponent<Scale>();
    auto tagComp = entity->getComponent<Tag>();
    auto windowSize = world.getWindow()->getSize();

    if (!posComp || !spriteComp || !scaleComp || !tagComp)
        return;

    auto sprite = spriteComp->getSprite();
    auto textureRect = sprite->getTextureRect();
    float scaleX = static_cast<float>(windowSize.x) / textureRect.size.x;
    float scaleY = static_cast<float>(windowSize.y) / textureRect.size.y;
    float finalScale = std::max(scaleX, scaleY);
    
    if (std::abs(scaleComp->getScale() - finalScale) > 0.001f) {
        scaleComp->setScale(finalScale * 1.2f);
    }

    float currentWidth = static_cast<float>(textureRect.size.x) * finalScale * 1.2f;

    std::string otherTag = (tagComp->getTag() == "background_first") ? "background_second" : "background_first";
    auto otherEntity = GameHelper::getEntityByTag(world, otherTag);

    if (posComp->getX() <= -currentWidth) {
        if (otherEntity) {
            auto otherPos = otherEntity->getComponent<Position>();
            if (otherPos) {
                posComp->setX(otherPos->getX() + currentWidth - 2.0f);
            }
        } else {
            posComp->setX(currentWidth);
        }
    }
    if (world.getCurrentScene() != entity->getComponent<Scene>()->getScene())
        entity->getComponent<Scene>()->setScene(world.getCurrentScene());
}

/**
 * @brief Updates the position of the player's fire entity.
 *
 * This function aligns the fire entity's position with the player's position.
 * @param entityId The ID of the fire entity.
 * @param world The game world containing entities and components.
 */

void playerfire(size_t entityId, World &world)
{
    auto fire = GameHelper::getEntityById(world, entityId);
    if (!fire)
        return;
    auto hp = fire->getComponent<HP>();
    if (hp && hp->getHP() <= 0)
        return;

    auto groupComp = fire->getComponent<Group>();
    if (!groupComp)
        return;

    size_t groupId = groupComp->getId();
    auto list = GameHelper::getEntitiesByGroup(world, groupId);
    std::shared_ptr<Entity> player = nullptr;

    for (const auto& e : list) {
        if (!e)
            continue;
        if (e->getId() == entityId)
            continue;

        auto tag = e->getComponent<Tag>();
        if (!tag)
            continue;

        if (tag->getTag() == "player" || tag->getTag() == "player_mate") {
            auto playerHp = e->getComponent<HP>();
            if (playerHp && playerHp->getHP() <= 0)
                continue;
            player = e;
            break;
        }
    }
    if (!player)
    return;
    auto musicComp = fire->getComponent<Music>();
    if (!musicComp)
        return;
    if (world.getCurrentScene() == static_cast<int>(SceneType::GAMEPLAY)) {
        musicComp->play();
    } else if (musicComp) {
        musicComp->stop();
    }
    auto posPlayer = player->getComponent<Position>();
    auto posFire = fire->getComponent<Position>();
    if (!posFire || !posPlayer)
        return;
    posFire->setX(posPlayer->getX() - 25.f);
    posFire->setY(posPlayer->getY() + 10.f);
}

/**
 * @brief Changes the scene of an entity to the current world scene.
 *
 * This function updates the scene component of the specified entity
 * to match the current scene of the game world.
 * @param entityId The unique ID of the entity.
 * @param world The game world containing entities and components.
 */
void changeSceneScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    entity->getComponent<Scene>()->setScene(world.getCurrentScene());
}

/**
 * @brief Updates the HP bar based on the entity's current HP.
 *
 * This function adjusts the scale of the HP bar sprite to reflect
 * the current health of the associated entity.
 * @param entityId The unique ID of the HP bar entity.
 * @param world The game world containing entities and components.
 */
void hpBarScript(int entityId, World& world)
{
    auto player = GameHelper::getEntityByTag(world, "player");
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!player || !entity)
        return;

    auto hpComp = player->getComponent<HP>();
    auto spriteComp = entity->getComponent<RectangleShape>();
    if (!hpComp || !spriteComp)
        return;
    float hp = static_cast<float>(hpComp->getHP());
    float maxHp = static_cast<float>(hpComp->getMaxHP());
    float scaleX = hp / maxHp;
    spriteComp->setSize(400.f * scaleX, 20.f);
}

/**
 * @brief Updates the Mana bar based on the entity's current Mana.
 *
 * This function adjusts the scale of the Mana bar sprite to reflect
 * the current mana of the associated entity.
 * @param entityId The unique ID of the Mana bar entity.
 * @param world The game world containing entities and components.
 */
void manaBarScript(int entityId, World& world)
{
    auto player = GameHelper::getEntityByTag(world, "player");
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!player || !entity)
        return;
    auto dataComp = player->getComponent<Data>();
    auto spriteComp = entity->getComponent<RectangleShape>();
    if (!dataComp || !spriteComp)
        return;
    int mana = std::stoi(dataComp->getData("mana"));
    int maxMana = 100;
    float scaleX = static_cast<float>(mana) / static_cast<float>(maxMana);
    spriteComp->setSize(400.f * scaleX, 10.f);
}

/**
 * @brief Script to handle player-specific behavior.
 *
 * This function can be expanded to include various player-related scripts.
 * @param entityId The ID of the player entity.
 * @param world The game world containing entities and components.
 */
void playerScript(int entityId, World& world)
{
    (void)entityId;
    auto player = GameHelper::getEntityByTag(world, "player");
    if (!player)
        return;
    auto dataComp = player->getComponent<Data>();
    if (!dataComp)
        return;
    auto newMana = std::stoi(dataComp->getData("mana")) + 2;
    if (newMana > 100)
        newMana = 100;
    dataComp->setData("mana", std::to_string(newMana));
}

/**
 * @brief Script to handle the logo dot behavior.
 *
 * This function adjusts the size and position of the logo dot based on
 * the space between two other logo elements.
 * @param entityId The ID of the dot entity.
 * @param world The game world containing entities and components.
 */
void dotScript(int entityId, World& world)
{
    auto dotEnt = GameHelper::getEntityById(world, entityId);
    if (!dotEnt || world.getCurrentScene() != static_cast<int>(SceneType::KAYU))
        return;
    float width = static_cast<float>(world.getWindow()->getSize().x);
    float height = static_cast<float>(world.getWindow()->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 3.0f;

    auto kayu = GameHelper::getEntityByTag(world, "logo_kayu");
    auto corp = GameHelper::getEntityByTag(world, "logo_corp");
    auto rect = dotEnt->getComponent<RectangleShape>();
    auto posDot = dotEnt->getComponent<Position>();
    static bool soundPlayed = false;
    
    if (!kayu || !corp || !rect || !posDot)
    return;

    float kayuRight = kayu->getComponent<Position>()->getX() + 150.f;
    float corpLeft = corp->getComponent<Position>()->getX() - 150.f;
    static bool used = false;
    float availableSpace = corpLeft - kayuRight;


    if (availableSpace < 2000.0f && availableSpace > 221.f) {
        rect->setSize(availableSpace, rect->getSize().y + 10.0f);
        if (!soundPlayed) {
            dotEnt->getComponent<SoundEffect>()->play();
            soundPlayed = true;
        }
    } else if (availableSpace <= 221.f) {
        if (!used) {
            EffectFactory::createSparks(world, centerX, centerY, 20);
            EffectFactory::createSparks(world, centerX, centerY + 100.f, 20);
            used = true;
        }
        rect->setSize(9.0f, 1000.f);
        posDot->setY(centerY - 90.f - 300.f);
        posDot->setX(centerX);
    } else {
        posDot->setY(centerY);
        posDot->setX(centerX - 100.f);
    }
}

/**
 * @brief Script to handle the Kayu logo behavior.
 *
 * This function manages the movement and sound playback of the Kayu logo.
 * @param entityId The ID of the Kayu entity.
 * @param world The game world containing entities and components.
 */
void myamboScript(int entityId, World& world)
{
    float width = static_cast<float>(world.getWindow()->getSize().x);
    float height = static_cast<float>(world.getWindow()->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 4.0f;
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    
    auto text = entity->getComponent<Text>();
    auto musicComp = entity->getComponent<SoundEffect>();
    auto posComp = entity->getComponent<Position>();
    if (!text || !musicComp || !posComp)
        return;

    static float currentSize = 10.0f;
    static float growthRate = 0.05f;
    static bool musicPlayed = false;

    posComp->setY(centerY);
    posComp->setX(centerX - (text->getGlobalBounds().size.x / 2.0f));
    if (currentSize < 200.0f) {
        if (!musicPlayed) {
            musicComp->play();
            musicPlayed = true;
        }
        growthRate += 0.003f; 
        currentSize += currentSize * growthRate;
        text->setSize(static_cast<unsigned int>(currentSize));
        posComp->setX(centerX - (text->getGlobalBounds().size.x / 2.0f));
    }
}

/**
 * @brief Script to handle the Myambo logo behavior.
 *
 * This function changes the text color of the Myambo logo after a certain size is reached.
 * @param entityId The ID of the Myambo entity.
 * @param world The game world containing entities and components.
 */
void productionScript(int entityId, World& world)
{
    float width = static_cast<float>(world.getWindow()->getSize().x);
    float height = static_cast<float>(world.getWindow()->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 4.0f;
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    
    auto text = entity->getComponent<Text>();
    auto posComp = entity->getComponent<Position>();
    auto dataComp = entity->getComponent<Data>();
    if (!text || !posComp || !dataComp)
        return;

    auto myamboEntity = GameHelper::getEntityByTag(world, "logo_myambo");
    if (!myamboEntity)
        return;

    auto myamboText = myamboEntity->getComponent<Text>();
    auto myamboPos = myamboEntity->getComponent<Position>();
    if (!myamboText || !myamboPos)
        return;
    auto musicComp = entity->getComponent<SoundEffect>();
    if (!musicComp)
        return;

    posComp->setY(centerY + 220.f);
    posComp->setX(centerX - (text->getGlobalBounds().size.x / 2.0f));
    static bool colorChanged = false;
    static bool musicPlayed = false;
    static int timer = 90;
    if (myamboText->getSize() >= 199 && !colorChanged) {
        if (timer > 0) {
            timer--;
            if (!musicPlayed && timer <= 16) {
                musicComp->play();
                musicPlayed = true;
            }
            return;
        }
        text->setColor(255, 255, 255, 255);
        colorChanged = true;
        posComp->setX(myamboPos->getX() + 150.f);
        dataComp->setData("displayed", "true");
    }
}

/**
 * @brief Script to handle the Kayu logo behavior.
 *
 * This function manages the movement and sound playback of the Kayu logo.
 * @param entityId The ID of the Kayu entity.
 * @param world The game world containing entities and components.
 */
void kayuScript(int entityId, World& world)
{
    auto e = GameHelper::getEntityById(world, entityId);
    if (!e || world.getCurrentScene() != static_cast<int>(SceneType::KAYU))
        return;
    float width = static_cast<float>(world.getWindow()->getSize().x);
    float height = static_cast<float>(world.getWindow()->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 3.0f;

    auto pos = e->getComponent<Position>();
    auto vel = e->getComponent<Velocity>();
    float targetX = centerX - 480.f;
    static bool soundPlayed = false;
    if (!pos || !vel)
        return;

    pos->setY(centerY);
    if (pos->getX() < targetX) {
        if (!soundPlayed) {
            e->getComponent<SoundEffect>()->play();
            soundPlayed = true;
        }
        vel->setVelocityX(vel->getVelocityX() * 1.05f);
        if (pos->getX() + vel->getVelocityX() * world.getDeltaTime() >= targetX) {
            pos->setX(targetX);
            vel->setVelocityX(0.f);
        }
        return;
    }
    pos->setX(pos->getX());
}

/**
 * @brief Script to handle the Corp logo behavior.
 *
 * This function manages the movement and sound playback of the Corp logo.
 * @param entityId The ID of the Corp entity.
 * @param world The game world containing entities and components.
 */
void corpScript(int entityId, World& world)
{
    auto e = GameHelper::getEntityById(world, entityId);
    if (!e || world.getCurrentScene() != static_cast<int>(SceneType::KAYU))
        return;
    float width = static_cast<float>(world.getWindow()->getSize().x);
    float height = static_cast<float>(world.getWindow()->getSize().y);
    float centerX = width / 2.0f;
    float centerY = height / 3.0f;

    auto pos = e->getComponent<Position>();
    auto vel = e->getComponent<Velocity>();
    if (!pos || !vel)
        return;
    float targetX = centerX + 20.f;

    pos->setY(centerY);
    if (pos->getX() > targetX) {
        vel->setVelocityX(vel->getVelocityX() * 1.05f);
        if (pos->getX() + vel->getVelocityX() * world.getDeltaTime() <= targetX) {
            pos->setX(targetX);
            vel->setVelocityX(0.f);
        }
        return;
    }
    pos->setX(pos->getX());
}

/**
 * @brief Script to handle the Myambo glow effect.
 *
 * This function updates the position and color of the Myambo glow text
 * to create a glowing effect around the Myambo logo.
 * @param entityId The ID of the Myambo glow entity.
 * @param world The game world containing entities and components.
 */
void myamboGlowScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto pos = entity->getComponent<Position>();
    auto text = entity->getComponent<Text>();
    auto myambo = GameHelper::getEntityByTag(world, "logo_myambo");
    if (!pos || !myambo)
        return;
    pos->setX(myambo->getComponent<Position>()->getX() + 10);
    pos->setY(myambo->getComponent<Position>()->getY() + 5);
    auto size = myambo->getComponent<Text>()->getSize();
    static float hue = 0.f;
    hue += 0.5f;
    if (hue >= 360.f)
        hue = 0.f;
    sf::Color color = GameHelperGraphical::hueToRGB(hue);
    text->setColor(color.r, color.g, color.b, 200);
    text->setSize(size);
    if (rand() % 10 == 0) {
        text->setColor(255, 255, 255, 50);
    } else {
        text->setColor(color.r, color.g, color.b, 200);
    }
    if (rand() % 5 == 0) {
        pos->setX(pos->getX() + (rand() % 4 - 2));
    }
}

/**
 * @brief Script to handle the Production glow effect.
 *
 * This function updates the position and color of the Production glow text
 * to create a glowing effect around the Production logo.
 * @param entityId The ID of the Production glow entity.
 * @param world The game world containing entities and components.
 */
void productionGlowScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto pos = entity->getComponent<Position>();
    auto text = entity->getComponent<Text>();
    auto prod = GameHelper::getEntityByTag(world, "logo_production");
    auto dataComp = prod->getComponent<Data>();
    if (dataComp->getData("displayed") != "true")
        return;
    if (!pos || !prod)
        return;
    pos->setX(prod->getComponent<Position>()->getX() + 10);
    pos->setY(prod->getComponent<Position>()->getY() + 5);
    static float hue = 0.f;
    hue += 0.5f;
    if (hue >= 360.f)
        hue = 0.f;
    sf::Color color = GameHelperGraphical::hueToRGB(hue);
    text->setColor(color.r, color.g, color.b, 200);
}

/**
 * @brief Script to handle the Kayu glow effect.
 *
 * This function updates the position and color of the Kayu glow text
 * to create a glowing effect around the Kayu logo.
 * @param entityId The ID of the Kayu glow entity.
 * @param world The game world containing entities and components.
 */
void kayuGlowScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto pos = entity->getComponent<Position>();
    auto text = entity->getComponent<Text>();
    auto kayu = GameHelper::getEntityByTag(world, "logo_kayu");
    if (!pos || !kayu)
        return;
    pos->setX(kayu->getComponent<Position>()->getX() + 10);
    pos->setY(kayu->getComponent<Position>()->getY() + 5);
    static float hue = 0.f;
    hue += 0.5f;
    if (hue >= 360.f)
        hue = 0.f;
    sf::Color color = GameHelperGraphical::hueToRGB(hue);
    text->setColor(color.r, color.g, color.b, 200);
}

/**
 * @brief Script to handle the Corp glow effect.
 *
 * This function updates the position and color of the Corp glow text
 * to create a glowing effect around the Corp logo.
 * @param entityId The ID of the Corp glow entity.
 * @param world The game world containing entities and components.
 */
void corpGlowScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto pos = entity->getComponent<Position>();
    auto text = entity->getComponent<Text>();
    auto corp = GameHelper::getEntityByTag(world, "logo_corp");
    if (!pos || !corp)
        return;
    pos->setX(corp->getComponent<Position>()->getX() + 10);
    pos->setY(corp->getComponent<Position>()->getY() + 5);
    static float hue = 0.f;
    hue += 0.5f;
    if (hue >= 360.f)
        hue = 0.f;
    sf::Color color = GameHelperGraphical::hueToRGB(hue);
    text->setColor(color.r, color.g, color.b, 200);
}

/**
 * @brief Script to handle volume settings.
 *
 * This function can be expanded to manage volume settings in the game.
 * @param entityId The ID of the volume settings entity.
 * @param world The game world containing entities and components.
 */
void volumeSettingsScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto dataComp = entity->getComponent<Data>();
    if (!dataComp)
        return;
    auto entityMusic = world.getAllEntitiesWithComponent<Music>();
    for (const auto& musicEntity : entityMusic) {
        auto musicComp = musicEntity->getComponent<Music>();
        if (!musicComp)
            continue;
        int masterVolume = std::stoi(dataComp->getData("master_volume")) ;
        int musicVolume = std::stoi(dataComp->getData("music_volume"));
        int finalVolume = (masterVolume * musicVolume) / 100;
        musicComp->setVolume(finalVolume);
    }
    auto entitySfx = world.getAllEntitiesWithComponent<SoundEffect>();
    for (const auto& sfxEntity : entitySfx) {
        auto sfxComp = sfxEntity->getComponent<SoundEffect>();
        if (!sfxComp)
            continue;
        int masterVolume = std::stoi(dataComp->getData("master_volume")) ;
        int sfxVolume = std::stoi(dataComp->getData("sfx_volume"));
        int finalVolume = (masterVolume * sfxVolume) / 100;
        sfxComp->setVolume(finalVolume);
    }
}

/**
 * @brief Script to handle spark entity behavior.
 *
 * This function reduces the size and fades out the spark entity over time.
 * @param entityId The ID of the spark entity.
 * @param world The game world containing entities and components.
 */
void sparkScript(int id, World& w)
{
    auto e = GameHelper::getEntityById(w, id);
    if (!e) return;
    auto r = e->getComponent<RectangleShape>();
    if (r->getSize().x > 0.1f) {
        r->setSize(r->getSize().x * 0.8f, r->getSize().y * 0.8f);
        r->setColor(r->getColor().r, r->getColor().g * 0.8f, r->getColor().b, r->getColor().a);
    }
    else
        w.killEntity(id);
}

/**
 * @brief Script to handle the Credits screen behavior.
 *
 * This function centers the credits text on the screen.
 * @param entityId The ID of the credits entity.
 * @param world The game world containing entities and components.
 */
void creditsScript(int id, World& w)
{
    auto centerX = static_cast<float>(w.getWindow()->getSize().x) / 8.f;
    auto pos = GameHelper::getEntityById(w, id);
    if (!pos)
        return;
    auto positionComp = pos->getComponent<Position>();
    positionComp->setX(centerX);
}

/**
 * @brief Script to handle the Credits names behavior.
 *
 * This function centers the credits names text on the screen.
 * @param entityId The ID of the credits names entity.
 * @param world The game world containing entities and components.
 */
void creditsNameScript(int id, World& w)
{
    auto centerX2 = static_cast<float>(w.getWindow()->getSize().x) / 2.f;
    auto pos = GameHelper::getEntityById(w, id);
    if (!pos)
        return;
    auto positionComp = pos->getComponent<Position>();
    positionComp->setX(centerX2);
}

/**
 * @brief Script to handle availability settings.
 *
 * This function updates fonts based on the dyslexia mode setting.
 * @param entityId The ID of the settings entity.
 * @param world The game world containing entities and components.
 */
void availabilitySettingsScript(int entityId, World& world)
{
    (void)entityId;
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto dataComp = entity->getComponent<Data>();
    if (!dataComp)
        return;
    auto disclexiaMode = dataComp->getData("disclexia_mode") == "true" ? true : false;

    if (disclexiaMode && dataComp->getData("lastfont_used") != "dyslexic") {
        for (const auto& entity : world.getEntitiesWithAnyComponent<Text, GuiWidget>()) {
            if (!entity)
                continue;
            auto textComp = entity->getComponent<Text>();
            auto guiWidgetComp = entity->getComponent<GuiWidget>();
            if (textComp) {
                auto currentFont = textComp->getFontPath();
                if (currentFont.find("regular.ttf") != std::string::npos)
                    textComp->setFont("../assets/font/dyslexic.otf");
            }
            if (guiWidgetComp) {
                auto currentFont = guiWidgetComp->getFontPath();
                if (currentFont.find("regular.ttf") != std::string::npos)
                    guiWidgetComp->setFont("../assets/font/dyslexic.otf");
            }
        }
        dataComp->setData("lastfont_used", "dyslexic");
    } else if (!disclexiaMode && dataComp->getData("lastfont_used") != "regular") {
        for (const auto& entity : world.getEntitiesWithAnyComponent<Text, GuiWidget>()) {
            if (!entity)
                continue;
            auto textComp = entity->getComponent<Text>();
            auto guiWidgetComp = entity->getComponent<GuiWidget>();
            if (textComp) {
                auto currentFont = textComp->getFontPath();
                if (currentFont.find("dyslexic.otf") != std::string::npos)
                    textComp->setFont("../assets/font/regular.ttf");
            }
            if (guiWidgetComp) {
                auto currentFont = guiWidgetComp->getFontPath();
                if (currentFont.find("dyslexic.otf") != std::string::npos)
                    guiWidgetComp->setFont("../assets/font/regular.ttf");
            }
        }
        dataComp->setData("lastfont_used", "regular");
    }
}

/**
 * @brief Script to handle companion entity behavior.
 *
 * This function updates the position and appearance of the companion entity
 * based on its orbit around the player and its level.
 * @param entityId The ID of the companion entity.
 * @param world The game world containing entities and components.
 */
void companionScript(int entityId, World& world)
{
    auto companionEntity = GameHelper::getEntityById(world, entityId);
    auto playerEntity = GameHelper::getEntityByTag(world, "player");
    
    if (!companionEntity || !playerEntity)
        return;
    auto cPos = companionEntity->getComponent<Position>();
    auto cLayer = companionEntity->getComponent<Layer>();
    auto cData = companionEntity->getComponent<Data>();
    auto pPos = playerEntity->getComponent<Position>();

    if (!cPos || !pPos || !cData)
        return;
    float angle = std::stof(cData->getData("orbit_angle"));
    angle += 0.06f * world.getDeltaTime(); 
    cData->setData("orbit_angle", std::to_string(angle));
    float radiusY = 100.0f; 
    float radiusX = 40.0f;  
    float offsetX = std::cos(angle) * radiusX;
    float offsetY = std::sin(angle) * radiusY;
    cPos->setX(pPos->getX() + offsetX + 20.f);
    cPos->setY(pPos->getY() + offsetY);
    int pLayerVal = playerEntity->getComponent<Layer>() ? playerEntity->getComponent<Layer>()->getLayerId() : 10;
    if (std::cos(angle) < 0) {
        if (cLayer) cLayer->setLayerId(pLayerVal - 1);
        companionEntity->getComponent<Scale>()->setScale(1.5f); 
    } else {
        if (cLayer) cLayer->setLayerId(pLayerVal + 1);
        companionEntity->getComponent<Scale>()->setScale(1.8f);  
    }
    auto datacomp = companionEntity->getComponent<Data>();
    if (!datacomp)
        return;
    if (std::stoi(datacomp->getData("level")) == 1 && datacomp->getData("changed") == "false") {
        auto soundeffectEntity = world.createEntity();
        GameHelperGraphical::soundEffectEntity("../assets/sounds/companionLevelUp.mp3", 100.f, static_cast<int>(SceneType::GAMEPLAY), world);
        companionEntity->getComponent<Animator>()->resetAnimator(6, 6, 3.f, 120, 66, 30, 26, 0, 0);
        datacomp->setData("changed", "true");
    } else if (std::stoi(datacomp->getData("level")) == 2 && datacomp->getData("changed") == "false") {
        GameHelperGraphical::soundEffectEntity("../assets/sounds/companionLevelUp.mp3", 100.f, static_cast<int>(SceneType::GAMEPLAY), world);
        companionEntity->getComponent<Animator>()->resetAnimator(4, 4, 3.f, 299, 342, 33, 33, 0, 0);
        datacomp->setData("changed", "true");
    } else if (std::stoi(datacomp->getData("level")) == 3 && datacomp->getData("changed") == "false") {
        GameHelperGraphical::soundEffectEntity("../assets/sounds/companionLevelUp.mp3", 100.f, static_cast<int>(SceneType::GAMEPLAY), world);
        companionEntity->getComponent<Animator>()->resetAnimator(4, 4, 3.f, 299, 376, 35, 31, 0, 0);
        companionEntity->getComponent<Sprite>()->getSprite()->setColor(sf::Color(192, 192, 192, 255));
        datacomp->setData("changed", "true");
    } else if (std::stoi(datacomp->getData("level")) == 4 && datacomp->getData("changed") == "false") {
        GameHelperGraphical::soundEffectEntity("../assets/sounds/companionLevelUp.mp3", 100.f, static_cast<int>(SceneType::GAMEPLAY), world);
        companionEntity->getComponent<Animator>()->resetAnimator(4, 4, 3.f, 301, 406, 35, 29, 0, 0);
        companionEntity->getComponent<Sprite>()->getSprite()->setColor(sf::Color(255, 215, 0, 255));
        datacomp->setData("changed", "true");
    }
}

/**
 * @brief Script to handle companion laser entity behavior.
 *
 * This function checks the position of the companion laser and
 * removes it from the world if it goes off-screen.
 * @param entityId The ID of the companion laser entity.
 * @param world The game world containing entities and components.
 */
void companionLaserScript(int entityId, World& world)
{
    auto laserEntity = GameHelper::getEntityById(world, entityId);
    auto playerEntity = GameHelper::getEntityByTag(world, "player");
    if (!laserEntity || !playerEntity)
        return;
    auto lPos = laserEntity->getComponent<Position>();
    if (!lPos)
        return;
    auto window = world.getWindow();
    if (lPos->getX() > window->getSize().x + 100) {
        world.killEntity(entityId);
        return;
    }
}


void enemyScript(int entityId, World& world)
{
    auto e = GameHelper::getEntityById(world, entityId);
    if (!e || world.getCurrentScene() != static_cast<int>(SceneType::GAMEPLAY))
        return;

    auto data = e->getComponent<Data>();
    if (!data)
        return;
    int cooldown = std::stoi(data->getData("sound_cooldown"));
    if (cooldown > 0) {
        data->setData("sound_cooldown", std::to_string(cooldown - 1));
        return;
    }
    if (cooldown == 0 && rand() % 6000 == 0) {
        GameHelperGraphical::playRandomAmbianceEnemy(world);
        data->setData("sound_cooldown", "3000");
    }
}