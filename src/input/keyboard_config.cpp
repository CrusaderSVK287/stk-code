//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2015 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


#include "input/keyboard_config.hpp"

#include "io/xml_node.hpp"
#include "utils/log.hpp"

#include <SKeyMap.h>

#include <assert.h>

using namespace irr;


KeyboardConfig::KeyboardConfig()
              : DeviceConfig()
{
    setDefaultBinds();
    setPlugged();
}   // KeyboardConfig

// ----------------------------------------------------------------------------
/** Saves the configuration to a file. It writes the name for a gamepad
 *  config, saves the device specific parameters, and calls
 *  DeviceConfig::save() to save the rest.
 *  \param stream The stream to save to.
 */
void KeyboardConfig::save(std::ofstream& stream)
{
    stream << "<keyboard ";
    DeviceConfig::save(stream);
    stream << "</keyboard>\n\n";
}  // save

//------------------------------------------------------------------------------

bool KeyboardConfig::load(const XMLNode* config)
{
    const bool loaded = DeviceConfig::load(config);

    bool has_reset_race_binding = false;
    for (unsigned int i = 0; i < config->getNumNodes(); i++)
    {
        const XMLNode* action = config->getNode(i);
        std::string name;
        action->get("name", &name);
        if (name == KartActionStrings[PA_RESET_RACE])
        {
            has_reset_race_binding = true;
            break;
        }
    }

    // Profiles saved before PA_RESET_RACE used Backspace for rescue. Move
    // precisely that legacy default to R, leaving explicitly saved new
    // bindings unchanged.
    const Binding& rescue_binding = getBinding(PA_RESCUE);
    if (!has_reset_race_binding &&
        rescue_binding.getType() == Input::IT_KEYBOARD &&
        rescue_binding.getId() == IRR_KEY_BACK)
    {
        setBinding(PA_RESCUE, Input::IT_KEYBOARD, IRR_KEY_R);
    }

    return loaded;
}   // load

//------------------------------------------------------------------------------

void KeyboardConfig::setDefaultBinds()
{
    setBinding(PA_NITRO,       Input::IT_KEYBOARD, IRR_KEY_N);
    setBinding(PA_ACCEL,       Input::IT_KEYBOARD, IRR_KEY_UP);
    setBinding(PA_BRAKE,       Input::IT_KEYBOARD, IRR_KEY_DOWN);
    setBinding(PA_STEER_LEFT,  Input::IT_KEYBOARD, IRR_KEY_LEFT);
    setBinding(PA_STEER_RIGHT, Input::IT_KEYBOARD, IRR_KEY_RIGHT);
    setBinding(PA_DRIFT,       Input::IT_KEYBOARD, IRR_KEY_V);
    setBinding(PA_RESCUE,      Input::IT_KEYBOARD, IRR_KEY_R);
    setBinding(PA_FIRE,        Input::IT_KEYBOARD, IRR_KEY_SPACE);
    setBinding(PA_LOOK_BACK,   Input::IT_KEYBOARD, IRR_KEY_B);
    setBinding(PA_PAUSE_RACE,  Input::IT_KEYBOARD, IRR_KEY_ESCAPE);
    setBinding(PA_RESET_RACE,  Input::IT_KEYBOARD, IRR_KEY_BACK);

    setBinding(PA_MENU_UP,     Input::IT_KEYBOARD, IRR_KEY_UP);
    setBinding(PA_MENU_DOWN,   Input::IT_KEYBOARD, IRR_KEY_DOWN);
    setBinding(PA_MENU_LEFT,   Input::IT_KEYBOARD, IRR_KEY_LEFT);
    setBinding(PA_MENU_RIGHT,  Input::IT_KEYBOARD, IRR_KEY_RIGHT);
    setBinding(PA_MENU_SELECT, Input::IT_KEYBOARD, IRR_KEY_RETURN);
    setBinding(PA_MENU_CANCEL, Input::IT_KEYBOARD, IRR_KEY_ESCAPE);
}

//------------------------------------------------------------------------------
