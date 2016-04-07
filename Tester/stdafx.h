// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma warning(disable:4067)

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>
#include <functional>
#include <thread>
#include <algorithm>
#include <queue>
#include <regex>

using namespace std;

#include "../VEngineNative/glm/vec3.hpp" // glm::vec3
#include "../VEngineNative/glm/vec4.hpp" // glm::vec4
#include "../VEngineNative/glm/mat4x4.hpp" // glm::mat4
#include "../VEngineNative/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../VEngineNative/glm/gtc/constants.hpp" // glm::pi 
#include "../VEngineNative/glm/gtc/quaternion.hpp"
#include "../VEngineNative/glm/gtc/type_ptr.hpp"

#include "../VEngineNative/Media.h";

#include "../VEngineNative/Game.h";

#define PI 3.141592f
#define rad2deg(a) (a * (180.0f / PI))
#define deg2rad(a) (a * (PI / 180.0f))


// TODO: reference additional headers your program requires here