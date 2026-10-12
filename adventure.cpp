#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    int health = 3;
    int gold = 0;
    bool hasLantern = false;
    bool hasKey = false;
    bool hasCrystal = false;
    bool hasSword = false;
};

int choose(const vector<string>& options) {
    int choice = 0;

    while (true) {
        for (size_t i = 0; i < options.size(); ++i) {
            cout << "  " << i + 1 << ". " << options[i] << '\n';
        }
        cout << "\nChoose an option: ";

        if (cin >> choice && choice >= 1 &&
            choice <= static_cast<int>(options.size())) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Please enter a number from 1 to " << options.size() << ".\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void showStatus(const Player& player) {
    cout << "\n--- Status ---\n"
         << "Health: " << player.health << "/3\n"
         << "Gold: " << player.gold << '\n'
         << "Items: ";

    bool hasItem = false;
    if (player.hasLantern) {
        cout << "lantern ";
        hasItem = true;
    }
    if (player.hasKey) {
        cout << "silver key ";
        hasItem = true;
    }
    if (player.hasCrystal) {
        cout << "moon crystal ";
        hasItem = true;
    }
    if (player.hasSword) {
        cout << "rusty sword ";
        hasItem = true;
    }
    if (!hasItem) {
        cout << "none";
    }
    cout << "\n--------------\n\n";
}

bool surviveTrap(Player& player) {
    cout << "\nThe floor gives way beneath you!\n";
    if (player.hasLantern) {
        cout << "Your lantern reveals a safe ledge, and you pull yourself up.\n";
        return true;
    }

    cout << "You fall into a hidden pit and hurt yourself.\n";
    --player.health;
    return player.health > 0;
}

void playGame() {
    Player player;

    cout << R"(
========================================
       THE MOONLIT RUINS
   A Choose Your Own Adventure Game
========================================
)";
    cout << "\nYou are standing at the edge of an ancient forest.\n"
         << "Legend says the Moonlit Ruins hold a crystal that can grant one wish.\n"
         << "Tonight, the ruins have appeared for the first time in a hundred years.\n\n";

    showStatus(player);
    cout << "The forest path splits in two.\n";
    int choice = choose({"Follow a trail of blue mushrooms",
                         "Take the old stone road"});

    if (choice == 1) {
        cout << "\nThe mushrooms lead you to a quiet cabin.\n"
             << "Inside, you find a lantern and a note: \"Light reveals truth.\"\n";
        player.hasLantern = true;
        cout << "You take the lantern.\n";
    } else {
        cout << "\nThe stone road leads to a merchant beside a broken cart.\n";
        choice = choose({"Trade 2 gold for a lantern", "Continue without stopping"});
        if (choice == 1) {
            cout << "\nThe merchant laughs. \"You do not have any gold!\"\n"
                 << "He gives you a lantern anyway, impressed by your courage.\n";
            player.hasLantern = true;
        } else {
            cout << "\nYou continue down the road as the sun disappears.\n";
        }
    }

    showStatus(player);
    cout << "At midnight, you reach the ruins. A stone gate blocks the entrance.\n"
         << "Two statues stand beside it: one holds a key, the other a sword.\n";
    choice = choose({"Search the statue holding the key",
                     "Take the rusty sword",
                     "Push open the gate"});

    if (choice == 1) {
        cout << "\nThe statue's hand opens. You take a silver key.\n";
        player.hasKey = true;
    } else if (choice == 2) {
        cout << "\nThe sword comes free with a groan. It is rusty, but still sharp.\n";
        player.hasSword = true;
    } else {
        cout << "\nThe gate opens with a thunderous rumble, but a stone falls from above.\n";
        --player.health;
        cout << "You are bruised. Health decreases.\n";
    }

    if (player.health <= 0) {
        cout << "\nYou collapse before the adventure truly begins.\n";
        return;
    }

    cout << "\nInside, the corridor divides.\n";
    choice = choose({"Enter the dark left corridor",
                     "Enter the glowing right corridor"});

    if (choice == 1) {
        cout << "\nThe darkness feels alive. You hear claws scraping stone.\n";
        if (!player.hasLantern) {
            cout << "Without a light, you stumble into a sleeping stone wolf.\n";
            if (player.hasSword) {
                cout << "Your sword scares it away.\n";
            } else {
                cout << "The wolf bites you before disappearing into the dark.\n";
                --player.health;
            }
        } else {
            cout << "Your lantern reveals a sleeping stone wolf. You quietly sneak past.\n";
        }
    } else {
        cout << "\nThe glowing corridor leads to a pool of shimmering water.\n"
             << "A voice whispers, \"Give what you value, and receive what you seek.\"\n";
        choice = choose({"Drop a gold coin into the pool",
                         "Reach into the water",
                         "Walk away"});
        if (choice == 1) {
            ++player.gold;
            player.hasCrystal = true;
            cout << "\nThe pool gives you a moon crystal in return.\n";
        } else if (choice == 2) {
            cout << "\nSomething cold grabs your hand!\n";
            --player.health;
            cout << "You pull free, but lose one health.\n";
        } else {
            cout << "\nThe voice fades, and the pool becomes ordinary water.\n";
        }
    }

    if (player.health <= 0) {
        cout << "\nYour wounds are too severe. The ruins claim another explorer.\n";
        return;
    }

    showStatus(player);
    cout << "At the heart of the ruins, you find a circular chamber.\n"
         << "A locked door bears an inscription: \"Only the honest may enter.\"\n";

    if (player.hasKey) {
        cout << "Your silver key fits the lock.\n";
        choice = choose({"Unlock the door", "Leave the ruins"});
        if (choice == 2) {
            cout << "\nYou leave safely, carrying a story no one will believe.\n";
            return;
        }
    } else {
        cout << "You have no key, but a narrow crack glows beside the door.\n";
        choice = choose({"Squeeze through the crack",
                         "Search the chamber for another way",
                         "Leave the ruins"});
        if (choice == 3) {
            cout << "\nYou decide that some mysteries are best left unsolved.\n";
            return;
        }
        if (choice == 2) {
            cout << "\nYou find a hidden lever, but activating it awakens the ruins.\n";
            --player.health;
        } else {
            cout << "\nYou squeeze through the crack and enter the treasure room.\n";
        }
    }

    if (player.health <= 0) {
        cout << "\nThe chamber seals shut. Your adventure ends in darkness.\n";
        return;
    }

    cout << "\nA moon crystal floats above a stone pedestal.\n";
    choice = choose({"Take the crystal and make a wish",
                     "Leave the crystal untouched",
                     "Destroy the crystal"});

    if (choice == 1) {
        cout << "\nYou reach for the crystal.\n";
        if (player.hasCrystal) {
            cout << "The two crystals resonate, filling the chamber with moonlight.\n";
            cout << "ENDING: The Moon Keeper\n"
                 << "You become guardian of the ruins and protect its magic forever.\n";
        } else if (player.hasLantern) {
            cout << "The lantern's light reveals that the crystal is genuine.\n";
            cout << "Your wish is granted: the forest blooms all year round.\n"
                 << "ENDING: The Forest's Friend\n";
        } else {
            cout << "The crystal is a trap. The room begins to collapse!\n";
            if (player.hasSword) {
                cout << "You cut through hanging vines and escape with your life.\n"
                     << "ENDING: The Lucky Survivor\n";
            } else {
                cout << "You escape empty-handed, but alive.\n"
                     << "ENDING: The Narrow Escape\n";
            }
        }
    } else if (choice == 2) {
        cout << "\nYou leave the crystal where it is.\n"
             << "The ruins reward your restraint with a chest of gold.\n"
             << "ENDING: The Wise Explorer\n";
    } else {
        cout << "\nThe crystal shatters. Every light in the ruins goes out.\n"
             << "You hear the forest whisper your name.\n"
             << "ENDING: The Cursed Wish\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        playGame();
        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << '\n';
    }

    cout << "Thanks for playing!\n";
    return 0;
}
