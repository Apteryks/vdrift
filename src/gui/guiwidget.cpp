/************************************************************************/
/*                                                                      */
/* This file is part of VDrift.                                         */
/*                                                                      */
/* VDrift is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* VDrift is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with VDrift.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                      */
/************************************************************************/

#include "guiwidget.h"
#include "hsvtorgb.h"
#include "graphics/drawable.h"

GuiWidget::GuiWidget() :
	m_alpha(1),
	m_visible(true),
	m_update(false)
{
	m_rgb[0] = 1, m_rgb[1] = 1, m_rgb[2] = 1;
	m_hsv[0] = 0, m_hsv[1] = 0, m_hsv[2] = 1;
	set_visible.bind<GuiWidget, &GuiWidget::SetVisible>(this);
	set_opacity.bind<GuiWidget, &GuiWidget::SetOpacity>(this);
	set_hue.bind<GuiWidget, &GuiWidget::SetHue>(this);
	set_sat.bind<GuiWidget, &GuiWidget::SetSat>(this);
	set_val.bind<GuiWidget, &GuiWidget::SetVal>(this);
}

void GuiWidget::Update(SceneNode & scene, float /*dt*/)
{
	if (m_update)
	{
		Drawable & d = GetDrawable(scene);
		d.SetColor(m_rgb[0], m_rgb[1], m_rgb[2], m_alpha);
		d.SetDrawEnable(m_visible && m_alpha > 0);
		m_update = false;
	}
}

void GuiWidget::SetAlpha(SceneNode & scene, float value)
{
	GetDrawable(scene).SetColor(m_rgb[0], m_rgb[1], m_rgb[2], m_alpha * value);
}

bool GuiWidget::GetProperty(const std::string & name, Delegated<const std::string &> *& slot)
{
	if (name == "hue")
		return (slot = &set_hue);
	if (name == "sat")
		return (slot = &set_sat);
	if (name == "val")
		return (slot = &set_val);
	if (name == "opacity")
		return (slot = &set_opacity);
	if (name == "visible")
		return (slot = &set_visible);
	return (slot = NULL);
}

void GuiWidget::SetOpacity(float value)
{
	m_alpha = value;
	m_update = true;
}

void GuiWidget::SetHue(float value)
{
	m_hsv[0] = value;
	HSVtoRGB(m_hsv, m_rgb);
	m_update = true;
}

void GuiWidget::SetSat(float value)
{
	m_hsv[1] = value;
	HSVtoRGB(m_hsv, m_rgb);
	m_update = true;
}

void GuiWidget::SetVal(float value)
{
	m_hsv[2] = value;
	HSVtoRGB(m_hsv, m_rgb);
	m_update = true;
}

void GuiWidget::SetVisible(const std::string & value)
{
	if (value.empty()) return;

	bool v = false;
	std::istringstream s(value);
	s >> std::boolalpha >> v;
	m_visible = v;
	m_update = true;
}

void GuiWidget::SetOpacity(const std::string & value)
{
	if (value.empty()) return;

	std::istringstream s(value);
	float v;
	s >> v;
	SetOpacity(v);
}

void GuiWidget::SetHue(const std::string & value)
{
	if (value.empty()) return;

	std::istringstream s(value);
	float v;
	s >> v;
	SetHue(v);
}

void GuiWidget::SetSat(const std::string & value)
{
	if (value.empty()) return;

	std::istringstream s(value);
	float v;
	s >> v;
	SetSat(v);
}

void GuiWidget::SetVal(const std::string & value)
{
	if (value.empty()) return;

	std::istringstream s(value);
	float v;
	s >> v;
	SetVal(v);
}
