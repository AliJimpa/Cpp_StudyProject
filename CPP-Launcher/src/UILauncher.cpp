
#include "UILauncher.h"
#include "W_HelloWorld.h"
#include "W_TEST.h"
#include "W_Demo.h"

UILauncher::UILauncher(App *owner) : UserInterface(owner)
{
    CreateWidget<W_HelloWorld>();
    CreateWidget<W_TEST>();
    CreateWidget<W_Demo>();
}