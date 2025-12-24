#include "cli/cli.h"
#include "app/chat_app.h"

int main(int argc, char* argv[]) {
    auto options = parseCLI(argc, argv);
    ChatApp app(options);
    app.run();
}
