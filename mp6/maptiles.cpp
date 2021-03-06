/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	MosaicCanvas* ret = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	vector< Point<3> > pointS;
	map<Point<3>, TileImage> tiles;
	RGBAPixel px;
	Point<3> pt;
	int i = 0;
	while(i<theTiles.size()){
		px = theTiles[i].getAverageColor();
		pt = Point<3>(px.red, px.green, px.blue);
		pointS.push_back(pt);
		tiles[pt] = theTiles[i];
		//pointS.push_back(pt);
		i++;
	}

	KDTree<3> tree(pointS);
	int x = 0;
	while(x<theSource.getRows()){
		int y = 0;
		while(y<theSource.getColumns()){
			px = theSource.getRegionColor(x,y);
			pt = Point<3>(px.red, px.green, px.blue);
			pt = tree.findNearestNeighbor(pt);
			ret->setTile(x, y, tiles[pt]);
			y++;
		}
		x++;
	}
	return ret;
}
