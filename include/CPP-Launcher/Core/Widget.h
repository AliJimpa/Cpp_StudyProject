#pragma once

class UserInterface;
class App;

class Widget
{
public:
    Widget(UserInterface *owner , App* application) : MyOwner(owner),MyApp(application) {};
    virtual void OnRender() {};

protected:
    UserInterface *GetUI() { return MyOwner; }
    App* GetApp() { return MyApp; }

private:
    UserInterface *MyOwner;
    App *MyApp;
};