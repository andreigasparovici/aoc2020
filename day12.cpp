#include <bits/stdc++.h>
using namespace std;

const double PI = 3.141592653589793;

vector<pair<char, int>> instructions;

double deg2rad(double theta) { return theta * PI / 180; }

struct Ship;

struct Waypoint {
	double dx, dy;

	Waypoint(int dx, int dy) : dx(dx), dy(dy) {}

	void moveNorth(int d) { dy += d; }

	void moveSouth(int d) { dy -= d; }

	void moveEast(int d) { dx += d; }

	void moveWest(int d) { dx -= d; }

	void turnLeft(double a) {
		a = deg2rad(a);
		tie(dx, dy) = make_pair(dx * cos(a) - dy * sin(a), dx * sin(a) + dy * cos(a));
	}
	void turnRight(int a) { turnLeft(-a); }
};

struct Ship {
	int initialX, initialY;
	double x, y;
	double thetaDeg;

	Ship(double x, double y, double thetaDeg) : x(x), y(y), thetaDeg(thetaDeg) {
		initialX = x;
		initialY = y;
	}

	double manhattan() { return abs(x - initialX) + abs(y - initialY); }

	void moveNorth(int d) { y += d;	}

	void moveSouth(int d) { y -= d; }

	void moveEast(int d) { x += d; }

	void moveWest(int d) { x -= d; }

	void turnLeft(int a) { thetaDeg -= a; }

	void turnRight(int a) { thetaDeg += a; }

	void moveForward(int d) {
		double theta = deg2rad(thetaDeg);
		x += d * cos(theta);
		y += d * sin(theta);
	}

	void moveTowards(const Waypoint& waypoint, int d) {
		x += d * waypoint.dx;
		y += d * waypoint.dy;
	}
};


void read() {
	fseek(stdin, 0, SEEK_SET);
	instructions.clear();

	char action;
	int value;

	while (scanf("%c%d\n", &action, &value) == 2)
		instructions.emplace_back(action, value);
}

void part1() {
	read();

	Ship ship(0, 0, 0);

	for (const auto& ins: instructions) {
		switch(ins.first) {
			case 'F':
				ship.moveForward(ins.second);
				break;
			case 'N':
				ship.moveNorth(ins.second);
				break;
			case 'S':
				ship.moveSouth(ins.second);
				break;
			case 'E':
				ship.moveEast(ins.second);
				break;
			case 'W':
				ship.moveWest(ins.second);
				break;
			case 'L':
				ship.turnLeft(ins.second);
				break;
			case 'R':
				ship.turnRight(ins.second);
				break;
		}
	}

	printf("%.0lf\n", ship.manhattan());
}

void part2() {
	read();

	Ship ship(0, 0, 0);
	Waypoint waypoint(10, 1);

	for (const auto& ins: instructions) {
		switch(ins.first) {
			case 'N':
				waypoint.moveNorth(ins.second);
				break;
			case 'S':
				waypoint.moveSouth(ins.second);
				break;
			case 'E':
				waypoint.moveEast(ins.second);
				break;
			case 'W':
				waypoint.moveWest(ins.second);
				break;
			case 'L':
				waypoint.turnLeft(ins.second);
				break;
			case 'R':
				waypoint.turnRight(ins.second);
				break;
			case 'F':
				ship.moveTowards(waypoint, ins.second);
				break;
		}
	}

	printf("%.0lf\n", ship.manhattan());
}

int main() {
	freopen("day12.in", "r", stdin);

	part1();
	part2();

	return 0;
}
