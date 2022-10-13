#include "SDL.h"
#include "config.hpp"
#include <qthread.h>
#include <unistd.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include "audio_device_config.hpp"
#include "doctest.h"
#include "program.hpp"
#include "tester.hpp"

#include <QApplication>
#include <QFile>
#include <iostream>
#include <thread>

#define WRAPPING 1

/* / *****!SECTION

Fix bug when hanging up while handshaking to reset on call boolean in call_gui class


******/
static Config *conf = Config::get_instance();

int main(int argc, char *argv[]) {

  Logger::setPriority(static_cast<logPriority>(conf->get<int>("LOGGER_LEVEL")));
  // This will run tests only when --test is passed to client
  int res = Tester::test(argc, argv);

  if (res > 0) {
    return res;
  }

  Uint32 subsystem_init = 0;

  if (SDL_WasInit(subsystem_init & SDL_INIT_AUDIO) <= 0) {
    SDL_Init(SDL_INIT_AUDIO);
  }

  QApplication a(argc, argv);
  QFile stylesheetFile("../misc/stylesheet/stylesheet.qss");
  stylesheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(stylesheetFile.readAll());
  a.setStyleSheet(styleSheet);

  Program *program = new Program();

  res = a.exec();

  delete program;

  SDL_Quit();

  QThread::sleep(WRAPPING);

  return res;
}
