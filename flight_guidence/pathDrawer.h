#include "cs225/PNG.h"
#include "cs225/graph.h"
#include "airlineFlow.h"
#include <unordered_map>

using std::pair;
using std::vector;
using std::string;
using std::unordered_map;
using cs225::PNG;
using cs225::HSLAPixel;

class PathDrawer {
    public:
        /**
         * Constructor of PathDrawer
         * @param airports the airport data
         */
        PathDrawer(Airports* airports);

        /**
         * Add a vector of vertices to the PathDrawer, the lines from the first element in the list, 
         * through all the other elements in the list, to the last element in the list will be added. 
         * When rendered, the path will using the HSLAPixel specified which in default is blue.
         * @param list the list containing all the vertices
         * @param renderPixel the HSLAPixel used when rendering
         */
        void addPath(vector<Vertex> list, const HSLAPixel& renderPixel = HSLAPixel(240, 1, 0.5, 1));


        /**
         * Add a vector of airport IDs to the PathDrawer, the lines from the first element in the list, 
         * through all the other elements in the list, to the last element in the list will be added. 
         * When rendered, the path will using the HSLAPixel specified which in default is blue.
         * @param list the list containing all the IDs of the airports
         * @param renderPixel the HSLAPixel used when rendering
         */
        void addPath(vector<int> list, const HSLAPixel& renderPixel = HSLAPixel(240, 1, 0.5, 1));

        /**
         * Add a single path from one vertex to another.
         * When rendered, the path will using the HSLAPixel specified which in default is blue.
         * @param from the from vertex
         * @param to the to vertex
         * @param renderPixel the HSLAPixel used when rendering
         */
        void addPath(Vertex from, Vertex to, const HSLAPixel& renderPixel = HSLAPixel(240, 1, 0.5, 1));

        /**
         * Add a single path from one airport to another.
         * When rendered, the path will using the HSLAPixel specified which in default is blue.
         * @param from the from airport ID
         * @param to the to airport ID
         * @param renderPixel the HSLAPixel used when rendering
         */
        void addPath(int from, int to, const HSLAPixel& renderPixel = HSLAPixel(240, 1, 0.5, 1));

        /**
         * Remove a vector of vertices to the PathDrawer, the lines from the first element in the list, 
         * through all the other elements in the list, to the last element in the list will be removed. 
         * @param list the list containing all the vertices
         */
        void removePath(vector<Vertex> list);
        
        /**
         * Remove a vector of vertices to the PathDrawer, the lines from the first element in the list, 
         * through all the other elements in the list, to the last element in the list will be removed. 
         * @param list the list containing all the vertices
         */
        void removePath(vector<int> list);
        
        /**
         * Remove a single path from one vertex to another.
         * @param from the from vertex
         * @param to the to vertex
         */
        void removePath(Vertex from, Vertex to);

        /**
         * Remove a single path from one airport to another.
         * @param from the from airport ID
         * @param to the to airport ID
         */
        void removePath(int from, int to);

        /**
         * Render the path in a newly created PNG using all the paths stored in the instance
         * @returns a world map containig all the paths added
         */
        PNG* renderPath();

        /**
         * Render the path in a newly created PNG using all the paths stored in the instance, then 
         * outputs a world map containig all the paths added to the file specified.
         * @param fileName the name of the file to save to 
         */
        void renderPath(string fileName);

    private:

        /**
         * Draw a line on a PNG from one point to another using specified HSLAPixel
         * outputs a world map containig all the paths added to the file specified.
         * @param canvas the PNG used as canvas
         * @param x1 the x-coordinate of one end
         * @param y1 the y-coordinate of one end
         * @param x2 the x-coordinate of the other end
         * @param y2 the y-coordinate of the other end
         * @param renderPixel the HSLAPixel used when rendering
         */
        void _drawLine(PNG* canvas, int x1, int y1, int x2, int y2, HSLAPixel& renderPixel);
    
        /** Airports data */
        Airports* _airports;

        /** The canvas to draw on */
        PNG* _canvas;

        /** Center of the canvas, where has 0 latitude and 0 longitude */
        pair<int, int> _center;

        /** 
         * Pixels per degree 
         * First entry: number of pixels per degree of latitude
         * Second entry: number of pixels per degree of longitude
         */
        pair<double, double> _pixelPerDegree;

        /** Internal storage to store all the paths */
        unordered_map<string, HSLAPixel> _pathList;
        
};