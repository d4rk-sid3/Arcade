
int main(int ac, char **av)
{
    DLLoader *loaderMenuLogic("path_to_menu_lib");
    DLLoader *loaderMenuDisplay(av[1]);

    IDisplay *menuDisplay = loaderMenuDisplay.getInstance();
    IMenu *menuLogic = loaderMenuLogic.getInstance();

    std::tuple <std::string, std::string> tUple;
    std::string gameLibLogic;
    std::string gameLibDisplay;


    DLLoader *loaderGameLogic = nullptr;
    DLLoader *loaderGameDisplay = nullptr;

    IGame *gameLogic;
    IDisplay *gameDisplay;

    menuLogic.init();
    menuDisplay.init(menuLogic.getConfig());

    bool a = true;
    bool inMenu = false;

    while (a) {
        if (menuLogic.isRunning()) {
            if (menuDisplay.hasGotInputs()) {
                menuLogic.update(menuDisplay.getInputs());
            }
            menuDisplay.getUpdate(menuLogic.getConfig());
            menuDisplay.render();
            inMenu = true;
        }
        if (!menuLogic.isRunning()) {
            if (inMenu) {
                tUple = menuLogic.getChoices();
                loaderGameLogic(std::get<0>(tUple));
                loaderGameDisplay(std::get<1>(tUple));

                IDisplay *gameDisplay = loaderGameDisplay.getInstance();
                IGame *gameLogic = loaderGameLogic.getInstance();
                gameLogic.init();
                gameDisplay.init(gameLogic.getConfig());
                inMenu = false;
            }

            if (gameDisplay.hasGotInputs()) {
                gameLogic.update(gameDisplay.getInputs());
            }
            gameDisplay.getUpdate(gameLogic.getConfig());
            gameDisplay.render();
        }
    }
}