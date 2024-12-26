// main.cpp

#include "main.h"
#include "WatchyMoto.h"

WatchyMoto* watchy = nullptr;

void setup() {
    watchy = new WatchyMoto();
    watchy->init();
}

void loop() {}