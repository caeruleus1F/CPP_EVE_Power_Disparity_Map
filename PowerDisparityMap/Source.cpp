#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <string>
using std::string;

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using sf::Color;
using sf::VertexArray;
using sf::Vector2f;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Image;
using sf::Event;
using sf::Keyboard;
using sf::Points;

#include "Target.h"
#include "GenericMissileLauncher.h"
#include "GenericTurret.h"
using pdm::DAMAGE_REDUCTION_FACTOR;
using pdm::Target;
using pdm::Weapon;
using pdm::Hull;
using pdm::GenericTurret;
using pdm::GenericMissileLauncher;

Color TranslateDisparityToColor(float, float, float);
void OutputToCSV(float**, int, int);
void PurgeGrid(float**&, int);

int main()
{
	/**************************************************************************
	*
	*	VARIABLES
	*
	**************************************************************************/

	const int trans_depth = 1000;
	const int trans_increment = 1;
	const int t_incr = trans_depth / trans_increment;
	const int range_depth = 100000;
	const int range_increment = 100;
	const int r_incr = range_depth / range_increment;
	const float starting_range = 0.0F;

	float** grid = new float*[t_incr]();
	for (int i = 0; i < t_incr; ++i)
	{
		grid[i] = new float[r_incr]();
	}

	float transversal = 0.0F;
	float range = 0.0F;

	/* HANGAR OF PRE-DEFINED SHIPS */
	// AND I DO NOT LIKE THIS SOLUTION. I'D RATHER PASS IN THE OBJECT DIRECTLY
	// 9/30 but there's a problem with circular references, iirc.
	// what i have going now only works because of forward class declarations
	// in Target.h and Weapon.h header files that somehow also prevents objects
	// being passed in directly.

	GenericTurret sat(400.0F, 0.009625F, 45000.0F, 24000.0F, 380.0F, 3.5F);
	Target* serp_admiral = new Target(Hull(390.0F), &sat, "Serpentis Admiral");

	GenericTurret slat(400.0F, 0.0433F, 6000.0F, 10000.0F, 396.0F, 3.0F);
	Target* serp_lord_admiral = new Target(Hull(390.0F), &slat, "Serpentis Lord Admiral");

	GenericTurret spat(400.0F, 0.01167F, 32500.0F, 20000.0F, 245.0F, 2.8F);
	Target* serp_port_admiral = new Target(Hull(360.0F), &spat, "Serpentis Port Admiral");

	GenericTurret sct(125.0F, 0.023F, 20000.0F, 12000.0F, 190.0F, 3.5F);
	Target* serp_captain = new Target(Hull(270.0F), &sct, "Serpentis Captain");

	GenericTurret gcit(125.0F, 0.023F, 25000.0F, 15000.0F, 176.0F, 3.5F);
	Target* guard_chief_infantry = new Target(Hull(160.0F), &gcit, "Guardian Chief Infantry");

	GenericTurret scsnt(125.0F, 0.028F, 90000.0F, 30000.0F, 525.0F, 2.8F);
	Target* serp_csn = new Target(Hull(90.0F), &scsnt, "Serpentis Clone Soldier Negotiator");

	//----- ^ NPC SHIPS | v PLAYER SHIPS -----//

	GenericTurret acmt(125.0F, 0.132F, 1500.0F, 12900.0F, 148.0F, 1.0F);
	Target* autocannon_maller = new Target(Hull(130.0F), &acmt, "Autocannon Maller");

	GenericTurret tt(40.0F, 0.0377F, 80190.0F, 9000.0F, 129.0F, 1.0F);
	Target* rail_corm = new Target(Hull(65.0F), &tt, "Rail Cormorant");
	Target* mwd_rail_corm = new Target(Hull(325.0F), &tt, "MWD Rail Cormorant");

	GenericMissileLauncher mm(500.0F, 40.0F, 250.0F, 10.0F, 60000.0F, pdm::LIGHT);
	Target* lm_corm = new Target(Hull(65.0F), &mm, "Light Missile Cormorant");

	GenericTurret algt(40.0, 0.498488F, 1687.0F, 1500.0F, 590.0F, 2.27F);
	Target* algos = new Target(Hull(66.0F), &algt, "Blaster Algos");

	GenericTurret catt(40.0F, 0.712F, 1688.0F, 4688.0F, 720.0F, 1.0F);
	Target* t2_cat = new Target(Hull(68.0F), &catt, "T2 Catalyst");

	GenericTurret vt(125.0F, 0.025625F, 18000.0F, 14400.0F, 514.0F, 1.0F);
	Target* vexor = new Target(Hull(145.0F), &vt, "Vexor");
	/* END HANGAR */

	// Chooses which ships to use for myself and the target.
	Target* m = vexor; // shows up in green
	Target* t = autocannon_maller;  // shows up in red

	/**************************************************************************
	*
	*	CALC POWER DISPARITY AND POPULATE GRID
	*
	**************************************************************************/

	float my_dps = 0.0F;
	float my_hit_chance = 0.0F;
	float tgt_dps = 0.0F;
	float tgt_hit_chance = 0.0F;
	float dps_disparity = 0.0F;

	float highest_disparity = 0.0F;
	float lowest_disparity = 0.0F;
	float abs_difference = 0.0F;
	float highest_range = 0.0F;
	float highest_trans = 0.0F;
	float lowest_range = 0.0F;
	float lowest_trans = 0.0F;

	for (int i = 0; transversal < trans_depth; ++i)
	{
		range = starting_range;

		for (int j = 0; range < range_depth; ++j)
		{
			my_dps = 0.0F;
			tgt_dps = 0.0F;
			dps_disparity = 0.0F;
			
			my_dps = m->CalcDPS(range, transversal, t);
			tgt_dps = t->CalcDPS(range, transversal, m);

			dps_disparity = my_dps - tgt_dps;

			// makes less work for the rendering stage when the color for 
			// every cell in the grid** doesn't have to be calculated,
			// only the cells that have values >= 1, since some
			// maps have a tendency to have large swaths of <1 disparity
			// and RGB is only granular to 8-bit anyway.
			if (abs(dps_disparity) < 1.0F)
			{
				dps_disparity = 0.0F;
			}

			if (dps_disparity > highest_disparity)
			{
				highest_disparity = dps_disparity;
				highest_range = range;
				highest_trans = transversal;
			}
			else if (dps_disparity < lowest_disparity)
			{
				lowest_disparity = dps_disparity;
				lowest_range = range;
				lowest_trans = transversal;
			}

			grid[i][j] = dps_disparity;
			range += range_increment;
		}

		transversal += trans_increment;
	}

	cout << "Range of highest disparity: " << highest_range << '\n';
	cout << "Trans of highest disparity: " << highest_trans << '\n';
	cout << "Range of lowest disparity: " << lowest_range << '\n';
	cout << "Trans of lowest disparity: " << lowest_trans << endl;

	/**************************************************************************
	*
	*	CREATE AND POPULATE MAP WITH COLORS DERIVED FROM DISPARITY VALUES.
	*
	**************************************************************************/

	VertexArray* map = new VertexArray[t_incr]();

	for (int i = 0; i < t_incr; ++i)
	{
		map[i].setPrimitiveType(Points);
		map[i].resize(r_incr);

		for (int j = 0; j < r_incr; ++j)
		{
			// flips the map about the x-axis so the origin is in the bottom left
			map[i][j].position = Vector2f((float)(i), (float)r_incr - 1 - j);
			map[i][j].color = TranslateDisparityToColor(grid[i][j], highest_disparity, lowest_disparity);
		}
	}

	/**************************************************************************
	*
	*	DRAW AXIS MARKINGS ON MAP.
	*
	**************************************************************************/
	int right_marking;
	int top_marking;
	for (int i = 0; i < 5; ++i) 
	{ 
		// Y-AXIS MARKINGS
		right_marking = r_incr - 1 - i;
		map[i][200].color = Color::Black; 
		map[right_marking][200].color = Color::Black;
		map[i][400].color = Color::Black; 
		map[right_marking][400].color = Color::Black;
		map[i][600].color = Color::Black; 
		map[right_marking][600].color = Color::Black;
		map[i][800].color = Color::Black; 
		map[right_marking][800].color = Color::Black;

		// X-AXIS MARKINGS
		top_marking = t_incr - 1 - i;
		map[200][i].color = Color::Black;
		map[200][top_marking].color = Color::Black;
		map[400][i].color = Color::Black;
		map[400][top_marking].color = Color::Black;
		map[600][i].color = Color::Black;
		map[600][top_marking].color = Color::Black;
		map[800][i].color = Color::Black;
		map[800][top_marking].color = Color::Black;
	}

	/**************************************************************************
	*
	*	MAIN WINDOW LOOP
	*
	**************************************************************************/

	RenderWindow window(VideoMode(t_incr, r_incr, 32U), "Power Disparity Map");
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(10);
	Image* img;

	while (window.isOpen())
	{
		Event e;

		// If user closes window.
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		// Clears the window and redraws map.
		// There's probably a better way to do this.
		window.clear(Color::White);
		for (int i = 0; i < t_incr; ++i)
		{
			window.draw(map[i]);
		}

		window.display();
		if (e.key.code == Keyboard::F1)
		{
			img = new Image();
			img->create(t_incr, r_incr);
			*img = window.capture();
			string m_ship_name(m->GetShipName());
			string t_ship_name(t->GetShipName());
			string file_name = m_ship_name + " vs. " + t_ship_name + ".jpg";
			img->saveToFile(file_name.c_str());
			delete img;
		}

		if (e.key.code == Keyboard::Escape)
		{
			window.close();
		}
	}

	/**************************************************************************
	*
	*	CLEANUP AND OPTIONAL STORAGE
	*
	**************************************************************************/

	//OutputToCSV(grid, t_incr, r_incr);
	PurgeGrid(grid, t_incr);
}

Color TranslateDisparityToColor(float disparity, float highest_disparity, float lowest_disparity)
{
	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 0;
	float disparity_to_use = highest_disparity;

	if (abs(lowest_disparity) > highest_disparity)
	{
		disparity_to_use = abs(lowest_disparity);
	}

	if (disparity > 0) // if the disparity is in my favor
	{
		red = 51;
		green = 255;
		blue = 51;
		alpha = static_cast<int>(255 * sin(disparity / disparity_to_use));

		if (disparity >= highest_disparity * .95) // attacker "crushing victory zone" color
		{
			red = 255;
			green = 204;
			blue = 5;
		}
	}
	else if (disparity < 0) // if the disparity is in the opponent's favor
	{
		red = 255;
		green = 51;
		blue = 51;
		alpha = static_cast<int>(255 * abs(disparity) / disparity_to_use);

		if (disparity <= lowest_disparity * .95) // target "crushing victory zone" color
		{
			red = 51;
			green = 102;
			blue = 0;
		}
	}
	else // if the disparity is 0
	{

	}

	return Color::Color(red, green, blue, alpha);
}

void PurgeGrid(float**& grid, int t_incr)
{
	for (int i = 0; i < t_incr; ++i)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

void OutputToCSV(float** grid, int t_incr, int r_incr)
{
	ofstream file("data.csv");

	for (int i = 0; i < t_incr; ++i)
	{
		for (int j = 0; j < r_incr; ++j)
		{
			file << grid[i][j];

			if (j + 1 < r_incr)
			{
				file << ',';
			}
		}

		file << '\n';
	}
	file.close();
}