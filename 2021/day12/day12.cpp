#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>

#include <iomanip>

class Cave {
public:
	enum class Size {
		SMALL,
		BIG
	};

	Cave() = delete;

	Cave(std::string cave_name)
		: name(cave_name) {
		size = Cave::getSize(cave_name);
	}

	void addConnection(Cave& cave) {
		connections.insert(cave.getName());
		if (!cave.hasConnection(*this)) { cave.addConnection(*this); }
	}

	bool hasConnection(const Cave& cave) {
		return connections.find(cave.getName()) != connections.end();
	}

	Cave::Size getSize() const { return size; }

	std::string getName() const { return name; }

	const std::unordered_set<std::string>& getConnections() {
		return connections;
	}

	static const std::string& startCaveName() {
		return START_CAVE_NAME;
	}

	static const std::string& endCaveName() {
		return END_CAVE_NAME;
	}
private:
	static Size getSize(std::string cave_name) {
		if (cave_name[0] >= 'A' && cave_name[0] <= 'Z') {
			return Size::BIG;
		} else { return Size::SMALL; }
	}

	static const std::string START_CAVE_NAME;
	static const std::string END_CAVE_NAME;

	Size size;
	std::string name;
	std::unordered_set<std::string> connections;
};

const std::string Cave::START_CAVE_NAME = std::string("start");
const std::string Cave::END_CAVE_NAME = std::string("end");

class Path {
public:
	bool addCave(const Cave& cave) {
		if (has_double_pass && passedSmallCave(cave)) { return false; }
		if (!cave_path.empty() && !cave_path.back().hasConnection(cave)) {
			return false;
		}

		cave_path.push_back(cave);
		if (cave.getSize() == Cave::Size::SMALL) {
			if (!small_caves.insert(cave.getName()).second) {
				has_double_pass = true;
				double_passed_cave_name = cave.getName();
			}
		}
		return true;
	}

	void removeLast() {
		if (cave_path.empty()) { return; }
		if (cave_path.back().getSize() == Cave::Size::SMALL) {
			if (hasDoublePass(cave_path.back().getName())) {
				has_double_pass = false;
				double_passed_cave_name.clear();
			} else { small_caves.erase(cave_path.back().getName()); }
		}
		cave_path.pop_back();
	}

	bool passedSmallCave(const Cave& cave) {
		if (small_caves.empty()) { return false; }
		if (cave.getSize() != Cave::Size::SMALL) { return false; }
		if (small_caves.find(cave.getName()) == small_caves.end()) { return false; }
		return true;
	}

	std::unordered_set<std::string> getPossibleConnections() {
		std::unordered_set<std::string> possible_connections;
		if (cave_path.empty() || cave_path.back().getName() == Cave::endCaveName()) {
			return possible_connections;
		}
		
		for (const Cave& cave : cave_path.back().getConnections()) {
			if (cave.getName() == Cave::startCaveName()) { continue; }

			if (cave.getSize() == Cave::Size::SMALL) {
				bool passed_small_cave = passedSmallCave(cave);
				if ((passed_small_cave && has_double_pass)
				|| (hasDoublePass(cave.getName()))) { continue; }
			}
			possible_connections.insert(cave.getName());
		}

		return possible_connections;
	}

	bool isComplete() {
		return cave_path.size() >= 2
			&& cave_path.front().getName() == Cave::startCaveName()
			&& cave_path.back().getName() == Cave::endCaveName();
	}

	void print() {
		for (const Cave& cave : cave_path) {
			std::cout << cave.getName() << ',';
		}
		std::cout << std::endl;
	}

	bool hasDoublePass() { return has_double_pass; }
private:
	bool hasDoublePass(std::string name) {
		return has_double_pass && (double_passed_cave_name == name);
	}

	bool has_double_pass = false;
	std::string double_passed_cave_name;
	std::list<Cave> cave_path;
	std::unordered_set<std::string> small_caves;
};

class CaveSystem {
public:
	CaveSystem(std::fstream& file) {
		std::string input_string;

		while (file >> input_string) {
			std::string name1, name2;
			std::string::size_type delimeter = input_string.find('-');
			if (delimeter == std::string::npos) { continue; }
			name1 = input_string.substr(0, delimeter);
			name2 = input_string.substr(delimeter+1);

			Cave& cave1 = caves.insert({name1, {name1}}).first->second;
			caves.insert({name2, {name2}}).first->second.addConnection(cave1);
		}
	}

	std::pair<uint32_t, uint32_t> findPaths() {
		uint32_t path_amount = 0u, double_pass_path_amount = 0u;

		cave_map_t::iterator start_cave = caves.find(Cave::startCaveName());
		if (start_cave == caves.end()) { return {0u, 0u}; }

		for (const auto& cave_name : start_cave->second.getConnections()) {
			cave_map_t::iterator cave = caves.find(cave_name);
			if (cave == caves.end()) { continue; }

			Path path;
			path.addCave(start_cave->second);
			path.addCave(cave->second);
			buildPaths(path, path_amount, double_pass_path_amount);
		}
		return {path_amount, double_pass_path_amount};
	}
private:
	typedef std::unordered_map<std::string, Cave> cave_map_t;

	void addCave(std::string name) {
		caves.insert({name, {name}});
	}

	void buildPaths(Path& path, uint32_t& path_amount,
			uint32_t& double_pass_path_amount) {
		std::unordered_set<std::string> possible_connections = path
			.getPossibleConnections();

		if (possible_connections.empty()) {
			if (path.isComplete()) {
				if (!path.hasDoublePass()) { ++path_amount; }
				++double_pass_path_amount;
			}
			return;
		}

		for(const auto& name : possible_connections) {
			path.addCave(caves.find(name)->second);
			buildPaths(path, path_amount, double_pass_path_amount);
			path.removeLast();
		}
	}

	cave_map_t caves;
};

int main() {
	std::fstream file("input.txt");
	CaveSystem cave_system(file);
	std::pair<uint32_t, uint32_t> results = cave_system.findPaths();
	std::cout << results.first << ' ' << results.second << std::endl;
	return 0;
}
