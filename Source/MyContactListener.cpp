#include "MyContactListener.h"

#include "Entity.h"
#include "Actor.h"
#include "Projectile.h"


MyContactListener::MyContactListener()
{}

void MyContactListener::BeginContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::EnemyActor, Category::AlliedProjectile))
    {
        auto& enemy = static_cast<Actor&>(*entities.first);
        auto& projectile = static_cast<Projectile&>(*entities.second);
        enemy.takeDamage(projectile.getDamage());
    }

    if(matchesCategory(entities, Category::PlayerActor, Category::LowerScene))
    {
        auto& player = static_cast<Actor&>(*entities.first);
        player.addFootContact();
    }

//    if(A->getCategory() == Category::EnemyActor && B->getCategory() == Category::AlliedProjectile)
//    {
//        Actor* actor = dynamic_cast<Actor*>(A);
//        Projectile* projectile = dynamic_cast<Projectile*>(B);
//        if(actor && projectile)
//            actor->takeDamage(5);
//    }
//    {
//        actor->addFootContact();
//        return;
//    }
//    actor = dynamic_cast<Actor*>(B);
//    if (actor)
//    {
//        actor->addFootContact();
//        return
//    }

}

void MyContactListener::EndContact(b2Contact* contact)
{
    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
    std::pair<Entity*, Entity*> entities = std::make_pair(A,B);

    if(matchesCategory(entities, Category::PlayerActor, Category::LowerScene))
    {
        auto& player = static_cast<Actor&>(*entities.first);
        player.removeFootContact();
    }



//    Entity* A = static_cast<Entity*>(contact->GetFixtureA()->GetUserData());
//    Entity* B = static_cast<Entity*>(contact->GetFixtureB()->GetUserData());
//    Actor* actor = dynamic_cast<Actor*>(A);
//    if (actor)
//    {
//        actor->removeFootContact();
//    }
//    actor = dynamic_cast<Actor*>(B);
//    if (actor)
//    {
//        actor->removeFootContact();
//    }
}

bool MyContactListener::matchesCategory(std::pair<Entity*,Entity*>& entities, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = entities.first->getCategory();
    unsigned int category2 = entities.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if(type1 & category2 && type2 & category1)
    {
        std::swap(entities.first, entities.second);
        return true;
    }
    else
    {
        return false;
    }
}
