#ifndef ACTIONCOMMAND_H
#define ACTIONCOMMAND_H

#include <vector>
#include <memory>
#include "ICommand.h"
#include "IWeapons.h"


class ActionCommand: public ICommand {
    public:
        ActionCommand(std::shared_ptr<Game> game) : ICommand(game) {}
        ~ActionCommand(){}

        void execute(std::vector<std::string> args) override {
            auto worm = mGame->getCurrentWorm();
            // Benutzt Baseball Schlaeger
            if(args.size() <= 0) {
                worm->useWeapon(worm->getPos().x, worm->getPos().y, " ", "melee");
                return;
            }
            // Überspringt Spielzug
            if (args.at(0) == "idle") return;
            // Ruft alle Waffen mit Richtung auf
            if (args.at(0) == "l" || args.at(0) == "r" || args.at(0) == "d" || args.at(0) == "u" ||
                    args.at(0) == "ld" || args.at(0) == "rd" || args.at(0) == "lu" || args.at(0) == "ru") {
                    auto impPoint = calculateImpactPoint(args.at(0), worm->getPos().x, worm->getPos().y);
                    if (impPoint.first == -1 && impPoint.second == -1) return;
                    worm->useWeapon(impPoint.first, impPoint.second, args.at(0));
                    return;
                } 
            // Ruft Airstrike
            if (args.size() == 1) {
                int col = 0;
                try {col = std::stoi(args.at(0));}
                catch (...) {
                    std::cout << "[Warning] Invalid input!" << std::endl;
                    return;
                }
                auto impPoint = calculateImpactPoint("d", col, 0);
                worm->useWeapon(impPoint.first, impPoint.second, " ", "airstrike");
                return;
            }
            // Ruft Teleporter
            if (args.size() == 2) {
                int x = 0;
                int y =0;
                try {
                    x = std::stoi(args.at(0));
                    y = std::stoi(args.at(1));
                }
                catch (...) {
                    std::cout << "[Warning] Invalid input!" << std::endl;
                    return;
                }
                worm->useWeapon(x, y, " ", "teleporter");
                return;
            }
        }



        std::pair<int, int> calculateImpactPoint(const std::string& direction, int wormX, int wormY) {
            int dx = 0, dy = 0;

            if (direction == "l") {
                dx = -1;
            } else if (direction == "r") {
                dx = 1;
            } else if (direction == "u") {
                dy = -1;
            } else if (direction == "d") {
                dy = 1;
            } else if (direction == "lu") {
                dx = -1;
                dy = -1;
            } else if (direction == "ru") {
                dx = 1;
                dy = -1;
            } else if (direction == "ld") {
                dx = -1;
                dy = 1;
            } else if (direction == "rd") {
                dx = 1;
                dy = 1;
            }

            int x = wormX + dx;
            int y = wormY + dy;

            // Traverse in the given direction until a solid block is found
            while (!mGame->getMap()->isSolidBlock(x, y)) {
                x += dx;
                y += dy;
                if (x < 0 || y < 0 || x > mGame->getMap()->getWidth()-1 || y > mGame->getMap()->getHeight()-1 ) {
                    std::cout << "Shoot missed..." << std::endl;
                    return {-1, -1};
                }
            }

            return {x, y};
        }
};

#endif // ACTIONCOMMAND_H