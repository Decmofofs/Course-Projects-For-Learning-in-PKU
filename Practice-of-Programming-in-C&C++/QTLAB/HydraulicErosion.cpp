#include "HydraulicErosion.h"
#include <random>
#include "objwriter.h"
#include "STrandom.h"
#include "setcolor.h"
#include "color_extension.h"
#include <QDebug>
#include "HeightGraphOperator.cpp"
#include "picturewidget.h"
#include <algorithm>
#include <time.h>
#include <queue>
using namespace std;


int posibilities::front = 224;
int posibilities::side = 78;
int posibilities::decrease = 56;
unsigned posibilities::speedDecrease = 48;
unsigned posibilities::speedSpread = 166;
int posibilities::erodeFront = 123;
int posibilities::erodeSide = 56;
int posibilities::erodeDown = 104;

int constvalue::direction4[9][2] = { {0,0},{1,0},{0,-1},{-1,0},{0,1},{1,0},{0,-1},{-1,0},{0,1} };
const int constvalue::height = 256, constvalue::width = 256;


static heightGraph grid(Vector2(0,0));
static bool used[2001][2001];
bool check(int x, int y) {
	if (x < 0 || y < 0 || x >= constvalue::height || y >= constvalue::width || grid[x][y] <= 0 || used[x][y]) return false;
	return true;
}

class water {
public:
	int x, y, h;
	unsigned d, v;
	water(int x, int y, int h) :x(x), y(y), h(h), d(0), v(255) {  }
	water(const water& w) :x(w.x), y(w.y), h(w.h), d(w.d), v(w.v) {  }
	water(const water& w, unsigned dir) : x(w.x + constvalue::direction4[dir][0]), y(w.y + constvalue::direction4[dir][1]), h(w.h), d(dir) { 
		if (d == w.d || d == 0) v = max(w.v - posibilities::speedDecrease - rand() % 5, 25u);
		else v = min(w.v, posibilities::speedSpread + rand() % 5);
	}

	void spread(queue<water>& Q) {
		if (d == 0) {
			for (int i = 1; i < 5; ++i) {
				Q.push(water(*this, i));
			}
		}
		else {
			if ((rand() % 256) < v) Q.push(water(*this, d));
			if ((rand() % 256) >= v) Q.push(water(*this, (d % 4) + 1));
			if ((rand() % 256) >= v)Q .push(water(*this, ((d + 2) % 4) + 1));
		}
	}

	void decrease() {
		if ((rand() % 256) >= v && h > grid[x][y] + 1) {
			--h;
			v = 255;
		}
	}

	void erode() {
		if ((rand() % 256) < posibilities::erodeDown && h > grid[x][y]) --grid[x][y];
		if (d) {
			int _x = x + constvalue::direction4[d][0];
			int _y = y + constvalue::direction4[d][1];
			if (check(_x, _y) && (rand() % 256) < posibilities::erodeFront && h <= grid[_x][_y]) --grid[_x][_y];
			_x = x + constvalue::direction4[d + 1][0];
			_y = y + constvalue::direction4[d + 1][1];
			if (check(_x, _y) && (rand() % 256) < posibilities::erodeSide && h <= grid[_x][_y]) --grid[_x][_y];
			_x = x + constvalue::direction4[d + 3][0];
			_y = y + constvalue::direction4[d + 3][1];
			if (check(_x, _y) && (rand() % 256) < posibilities::erodeSide && h <= grid[_x][_y]) --grid[_x][_y];
		}
	}
};
void update(){
    queue<water> Q;
	Q.push(water(rand() % constvalue::height, rand() % constvalue::width, 256));
	while (!Q.empty()) {
		//cout << Q.size() << endl;
		water p = Q.front();
		Q.pop();

		if (check(p.x, p.y)) {
			used[p.x][p.y] = true;
			p.decrease();
			p.erode();
			p.spread(Q);
		}

	}
	for (int i = 0; i < constvalue::height; ++i) {
		for (int j = 0; j < constvalue::width; ++j) {
			used[i][j] = false;
		}
	}
}
bool HydraulicErosion2D(int seed, int T){
    grid = heightGraph(Vector2(constvalue::height,constvalue::width));
    for(unsigned i = 0;i < constvalue::height; ++i){
        for(unsigned j = 0;j < constvalue::width; ++j){
            grid[i][j] = 255;
        }
    }
    memset(used,0,sizeof(used));
    int times = T;
    while(times--){
        update();
    }

    if (PictureWidget::MeshStyle == 0) objWriter::CubeMesh(grid, Vector2(0,0), "hydraulicerosionmesh");
    else objWriter::SmoothMesh(grid, Vector2(0,0), "hydraulicerosionmesh");
    if (PictureWidget::PrinterStyle == 0) bmp_reader::write("./HydraulicErosion.bmp", &grid, color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    else bmp_reader::write("./HydraulicErosion.bmp", &grid, cSimpleCopy());
    //objWriter::CubeMesh(grid,Vector2(0,0),"hydraulicerosionmesh");
    //bmp_reader::write("./HydraulicErosionGraph.bmp",&grid,color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    return 1;
}   

HydraulicErosionCal::HydraulicErosionCal(const int & _seed, const int & _T,QObject * parent)
    :QObject(parent),seed(_seed),T(_T)
{
    QObject::connect(this,&HydraulicErosionCal::ToDo,this,&HydraulicErosionCal::work);
}

void HydraulicErosionCal::work(){
    HydraulicErosion2D(seed,T);
}
