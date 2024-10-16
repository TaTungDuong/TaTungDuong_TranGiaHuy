#include "Include/Button.h"

void button::init(int x, int y, int s, std::string t, TTF_Font* f)
{
	px = float(x);
	py = float(y);
	size = s;
	text = t;
	font = f;
	h = size;
	w = h * 3.5;
	rx = px - w / 2;
	ry = py - h / 7.5;
	currentState = buttonState::DEFAULT;

	m_pBtClick = NULL;
}

bool button::checkInside(int x, int y)
{
	if (x > px - w / 2 &&
		x < px + w / 2 &&
		y > py - h / 2 &&
		y < py + h) {
		return true;
	}
	else {
		return false;
	}
}

void button::checkButton(Uint32 mouses, int x, int y)
{
	currentState = buttonState::DEFAULT;
	//check mouse input
	//if mouse is on the button
	if (checkInside(x, y))
	{
		currentState = buttonState::HOVERED;
		//if mouse is pressing the button
		if (mouses & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			currentState = buttonState::PRESSED;
		}
	}
}

void button::setText(std::string t)
{
	text = t;
}


void button::render(SDL_Renderer* target)
{
	//TODO: fix render
	//printf("px = %f, py = %f, rx = %i, ry = %i\n", px, py, rx, ry);
	SDL_Rect buttonRect{ rx, ry, w, h };

	//draw button rect
	switch (currentState)
	{
	case buttonState::DEFAULT:
		SDL_SetRenderDrawColor(target, 255, 255, 255, 255);
		SDL_RenderDrawRect(target, &buttonRect);
		break;
	case buttonState::HOVERED:
		SDL_SetRenderDrawColor(target, 255, 0, 0, 255);
		SDL_RenderFillRect(target, &buttonRect);
		SDL_SetRenderDrawColor(target, 200, 200, 200, 255);
		SDL_RenderDrawRect(target, &buttonRect);
		break;
	case buttonState::PRESSED:
		SDL_SetRenderDrawColor(target, 125, 0, 0, 255);
		SDL_RenderFillRect(target, &buttonRect);
		SDL_SetRenderDrawColor(target, 150, 150, 150, 255);
		SDL_RenderDrawRect(target, &buttonRect);
		break;
	}

	//draw text
	SDL_Color color = { 255, 255, 255 };
	drawText(px, py, font, color, text, 1);
}


bool button::HandleTouchEvent(SDL_Event* e)
{
	//If mouse event happened (clicked/released...
	if (e->type == SDL_MOUSEBUTTONUP)//|| e->type == SDL_MOUSEBUTTONDOWN) e->type == SDL_MOUSEMOTION || 
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		// Check if mouse is in button
		bool inside = true;
		//Mouse is left/right above/below of the button
		if (x < rx || x > rx + w || y < ry || y > ry + h)
		{
			inside = false;
		}
		// Mouse is outside button
		if (inside)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClick();
		}
		//if (e->button.button == SDL_BUTTON_LEFT)
		//{
			///  perform left click action when the same button was pressed down and released with m_pBtLeftClick() callback.
		//}
		return inside;
	}
	return false;
}

void button::SetOnClick(std::function<void(void)> pBtClick)
{
	m_pBtClick = pBtClick;
}
