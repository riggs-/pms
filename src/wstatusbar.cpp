/* vi:set ts=8 sts=8 sw=8:
 *
 * Practical Music Search
 * Copyright (c) 2006-2011  Kim Tore Jensen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "window.h"
#include "console.h"
#include "curses.h"
#include "input.h"
#include "config.h"
#include <cstring>
#include <string>
#include <vector>

using namespace std;

extern vector<Logline *> logbuffer;
extern Curses curses;
extern Windowmanager wm;
extern Input input;
extern Config config;

void Wstatusbar::drawline(int rely)
{
	vector<Logline *>::reverse_iterator i;

	curses.wipe(rect);

	switch(input.mode)
	{
		case INPUT_MODE_COMMAND:
			for (i = logbuffer.rbegin(); i != logbuffer.rend(); i++)
			{
				if ((*i)->level > MSG_LEVEL_INFO)
					continue;

				curses.print(rect, config.colors.statusbar, rely, 0, (*i)->line.c_str());
				break;
			}
			break;

		case INPUT_MODE_INPUT:
			curses.print(rect, config.colors.statusbar, rely, 0, ":");
			curses.print(rect, config.colors.statusbar, rely, 1, input.strbuf.c_str());
			break;
	}
}

void Wreadout::drawline(int rely)
{
	char		buf[4];
	Wmain *		win;

	win = WMAIN(wm.active);

	if (win->content_size() <= win->height())
		strcpy(buf, "All");
	else if (win->position == 0)
		strcpy(buf, "Top");
	else if (win->position >= win->content_size() - win->height() - 1)
		strcpy(buf, "Bot");
	else
		sprintf(buf, "%2d%%%%", 100 * win->position / (win->content_size() - win->height() - 1));

	curses.print(rect, config.colors.readout, 0, 0, buf);
}
