#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define ATOM_SIZE		3
#define MAX_FORCE 		10
#define ATTRACT_FORCE 	3
#define ATTRACT_EXP 	-2
#define REPEL_FORCE		4000
#define REPEL_EXP		-4

#define ATOM_NORMAL_COLOR	0xFFFFFFFF
#define ATOM_CLOSE_COLOR	0xFFFFFF00

double deltaTime;
int windowWidth;
int windowHeight;

typedef struct
{
	double x;
	double y;
} Vec2;

typedef struct
{
	double x;
	double y;
	double mass;
	Uint32 color;
} Atom;

double rand_normalized() {
	return (double)rand() / RAND_MAX;
}

Atom point2Atom(SDL_Point point) {
	return (Atom){
		.x = point.x,
		.y = point.y,
		.mass = 1,
		.color = ATOM_NORMAL_COLOR
	};
}

Vec2 normalize(Vec2 vector, double length) {
	return (Vec2){
		(double)vector.x / length,
		(double)vector.y / length
	};
}

double calculate_length(Vec2 vector) {
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

void colorize_atom(Atom *atom, double distance) {
	Uint32 colors[] = {
		0xFFF94144,
		0xFFF3722C,
		0xFFF8961E,
		0xFFF9C74F,
		0xFF90BE6D,
		0xFF43AA8B,
		0xFF577590
	};
	int num_colors = 7;
	atom->color = colors[(int)fmin(distance, num_colors - 1)];
}

void simulate(Atom *atoms, int num_atoms)
{
	Atom *atoms_og = atoms;
	for (int cur_atom = 0; cur_atom < num_atoms; ++cur_atom) {
		for (int ptr_atom = 0; ptr_atom < num_atoms; ++ptr_atom) {
			if (cur_atom == ptr_atom) {
				continue;
			}

			Vec2 vector = {
				atoms_og[ptr_atom].x - atoms_og[cur_atom].x,
				atoms_og[ptr_atom].y - atoms_og[cur_atom].y
			};

			if (vector.x == 0 && vector.y == 0) {
				vector = (Vec2){
					rand_normalized() * 100,
					rand_normalized() * 100,
				};
			}

			double vector_length = calculate_length(vector);

			double attract_force =
				pow(vector_length, ATTRACT_EXP) * ATTRACT_FORCE * -10000 * deltaTime;
			double repel_force =
				pow(vector_length, REPEL_EXP) * REPEL_FORCE * 10000 * deltaTime;

			attract_force = attract_force > 0
				? fmin(attract_force, MAX_FORCE)
				: fmax(attract_force, -1 * MAX_FORCE);
			repel_force = repel_force > 0
				? fmin(repel_force, MAX_FORCE)
				: fmax(repel_force, -1 * MAX_FORCE);

			double total_force = attract_force + repel_force;

			Vec2 normalized_vector = normalize(vector, vector_length);

			Vec2 force_vector = {
				normalized_vector.x * total_force,
				normalized_vector.y * total_force,
			};

			if (vector_length < ATOM_SIZE * 2) {
				force_vector.x += normalized_vector.x * (ATOM_SIZE * 2 - vector_length);
				force_vector.y += normalized_vector.y * (ATOM_SIZE * 2 - vector_length);
			}

			atoms[ptr_atom].x += force_vector.x;
			atoms[ptr_atom].y += force_vector.y;

			colorize_atom(&atoms[ptr_atom], vector_length);
		}
	}
}

double get_delta_time(Uint64 *now, Uint64 *last)
{
	*last = *now;
	*now = SDL_GetPerformanceCounter();
	return (double)((*now - *last) / (double)SDL_GetPerformanceFrequency());
}

void draw(SDL_Renderer *renderer, Atom *atoms, int num_atoms)
{
	for (int i = 0; i < num_atoms; ++i) {
		filledCircleColor(renderer, atoms[i].x, atoms[i].y, ATOM_SIZE, atoms[i].color);
	}
}

int main(void)
{
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "SDL could not be initialized!\n"
		  "SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	SDL_CreateWindowAndRenderer(
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE,
			&window, &renderer);

	Uint64 time_now = SDL_GetPerformanceCounter();
	Uint64 time_last = 0;

	SDL_Point mousepos;
	Atom *atoms = NULL;
	int num_atoms = 0;

	int running = 1;


	while (running) {
		SDL_SetRenderDrawColor(renderer, 0x24, 0x27, 0x3A, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_GetMouseState(&mousepos.x, &mousepos.y);
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		deltaTime = get_delta_time(&time_now, &time_last);

		printf("\rfps: %.1f", 1 / deltaTime);
		fflush(stdout);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						SDL_UpdateWindowSurface(window);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (int i = 0; i < 5; ++i) {
						atoms = realloc(atoms, ++num_atoms * sizeof(Atom));
						atoms[num_atoms - 1] = point2Atom(mousepos);
					}
					break;
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ){
						case SDLK_ESCAPE:
							running = 0;
							break;
					}
					break;
			}
		}

		simulate(atoms, num_atoms);

		draw(renderer, atoms, num_atoms);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}


	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();

	return 0;
}
