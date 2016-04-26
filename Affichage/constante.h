#pragma once

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>

const float INF = 1.0f / 0.0f;  // Infini en float.

const int widthscreen = 720;    //En pixel.
const int heightscreen = 540;   //En pixel.
const int widthdesc = 100;  //En pixel.
const int taille_case = 24; //En pixel.

const int widthmap = 300;   //En case.
const int heightmap = 300;  //En case.

extern Imagine::Image<Imagine::Color> foret1;
extern Imagine::Image<Imagine::Color> eau1;
extern Imagine::Image<Imagine::Color> lande1;

bool charge_image();
