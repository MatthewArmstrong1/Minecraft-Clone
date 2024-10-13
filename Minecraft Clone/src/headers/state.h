#pragma once

#ifndef STATE_H
#define STATE_H

#include "window.h"

class State {
	public:
		Window* currentWindow;

		State() = default;
};

#endif