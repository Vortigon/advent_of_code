#include <iostream>
#include <fstream>
#include <vector>

class Octopus {
public:
	Octopus(uint32_t light_lvl = 0) : light_level(light_lvl) {}

	bool hasFlashed() {
		return flashed;
	}

	void increaseLight() {
		if (flashed) { return; }
		++light_level;
	}

	void flash() {
		if (light_level > 9) {
			flashed = true;
			light_level = 0;
		}
	}

	bool hasEnoughLight() {
		return light_level > 9;
	}

	void fade() {
		flashed = false;
	}

	uint32_t getLightLevel() { return light_level; }
private:
	uint32_t light_level = 0;
	bool flashed = false;
};

class Cavern {
public:
	Cavern(std::fstream& file) {
		for (uint32_t i = 0; i < 10; ++i) {
			for (uint32_t j = 0; j < 10; ++j) {
				char symbol;
				file >> symbol;
				if (symbol > '9' || symbol < '0') { file >> symbol; }
				octopuses[i][j] = Octopus(symbol - '0');
			}
		}
	}

	void simulate(uint32_t steps) {
		first_sync_step = 0;
		uint32_t saved_flash_amount = 0;
		for (uint32_t step = 0; step < steps || first_sync_step == 0; ++step) {
			if (step == steps) { saved_flash_amount = flash_amount; }
			bool synced = true;
			for (uint32_t i = 0; i < 10; ++i) {
				for (uint32_t j = 0; j < 10; ++j) {
					octopuses[i][j].increaseLight();

					if (octopuses[i][j].hasEnoughLight()) {
						traceFlashes({i, j});
					}
				}
			}

			for (uint32_t i = 0; i < 10; ++i) {
				for (uint32_t j = 0; j < 10; ++j) {
					if (!octopuses[i][j].hasFlashed()) { synced = false; }
					else { octopuses[i][j].fade(); }
				}
			}
			if (synced && first_sync_step == 0) {
				first_sync_step = step+1;
				if (step >= steps) {
					flash_amount = saved_flash_amount; return;
				}
			}
		}
	}

	uint32_t getFlashAmount() {
		return flash_amount;
	}

	uint32_t getFirstSyncStep() {
		return first_sync_step;
	}
private:
	struct Cell {
		uint32_t x, y;
	};

	void traceFlashes(Cell trace_start) {
		std::vector<Cell> flash_trace;
		flash_trace.push_back(trace_start);

		while (!flash_trace.empty()) {
			Cell last_cell = flash_trace.back();
			flash_trace.pop_back();

			if (octopuses[last_cell.x][last_cell.y].hasFlashed()) { continue; }
			octopuses[last_cell.x][last_cell.y].flash();
			++flash_amount;
			increaseAdjacentLights(last_cell.x, last_cell.y);

			uint32_t startRow = last_cell.x > 0 ? last_cell.x-1 : last_cell.x;
			uint32_t endRow = last_cell.x < trace_start.x ? last_cell.x+1 : last_cell.x;
			uint32_t startCol = last_cell.y > 0 ? last_cell.y-1 : last_cell.y;
			uint32_t endCol = last_cell.y < 9 ? last_cell.y+1 : last_cell.y;

			for (uint32_t i = startRow; i <= endRow; ++i) {
				for (uint32_t j = startCol; j <= endCol; ++j) {
					if ((i == last_cell.x && j == last_cell.y)
					|| (i == trace_start.x && j >= trace_start.y)
					|| (!octopuses[i][j].hasEnoughLight())) {
						continue;
					}

					if (octopuses[i][j].hasEnoughLight()) {
						flash_trace.push_back({i, j});
					}
				}
			}
		}
	}

	void increaseAdjacentLights(uint32_t row, uint32_t col) {
		uint32_t startRow = row > 0 ? row-1 : row;
		uint32_t endRow = row < 9 ? row+1 : row;
		uint32_t startCol = col > 0 ? col-1 : col;
		uint32_t endCol = col < 9 ? col+1 : col;

		for (uint32_t i = startRow; i <= endRow; ++i) {
			for (uint32_t j = startCol; j <= endCol; ++j) {
				if (i != row || j != col) { octopuses[i][j].increaseLight(); }
			}
		}
	}

	uint32_t flash_amount = 0;
	uint32_t first_sync_step = 0;
	Octopus octopuses[10][10];
};

int main() {
	std::fstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	Cavern cavern(file);
	cavern.simulate(100);
	std::cout << cavern.getFlashAmount() << std::endl;
	std::cout << cavern.getFirstSyncStep() << std::endl;
	return 0;
}
