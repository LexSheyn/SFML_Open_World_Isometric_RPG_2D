#pragma once

// Add /Qvec-report:2 /Qpar-report:2
// to Properties -> C/C++ -> Command Line
// for vectorization and parallelization reports 

// C++ standard libraries
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <typeinfo>
#include <random>

// SFML (namespace sf::)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// FMOD (namespace FMOD::)
#include <FMOD/fmod.hpp>

// GUI (namespace gui::)
#include "Gui.h"

// Sound engine (namespace sfx::)
#include "SoundEngine.h"

// Windows library to hide Console window.
// Including Windows.h always couses weird errors
// but after some rebuilds they all be gone,
// I don't know why.
//	#include <Windows.h>