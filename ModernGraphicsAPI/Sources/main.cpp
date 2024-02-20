#include "App.hpp"
#include "Assertion.hpp"

int main()
{
    Log::OpenFile("Log.txt");

    Core::App* app = Core::App::Get();
    app->Create();
    app->Quit();

    Log::CloseFile();
}