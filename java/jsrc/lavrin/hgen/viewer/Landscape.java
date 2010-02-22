package lavrin.hgen.viewer;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;

import lavrin.hgen.*;

public class Landscape extends Shape3D 
{
  private final static int SIDE_LEN = 128;
    /* Should be even, since the code assumes that SIDE_LEN/2 is 
       a whole number. */

  private Heightmap hmap;
  private float[][] heights;   // height map for the floor


  public Landscape() {
    setCapability(ALLOW_GEOMETRY_READ);
    setCapability(ALLOW_GEOMETRY_WRITE);

    hmap = new CHeightmap(SIDE_LEN + 1, SIDE_LEN + 1);
    heights = makeHills();
    createGeometry();
    createAppearance();
  } // end of Landscape()


  public void update() {
//    hmap.faultingFilter(10, 5);
//    hmap.walkerFilter(10, 5);
    hmap.smoothFilter((short)1);

    Heightmap tmp = hmap.copy();
    tmp.normalize();
    tmp.scale(20.0);

    heights = tmp.toFloatArray();
    createGeometry();
  }


  private float[][] makeHills() {
//    float[][] heights = new float[SIDE_LEN+1][SIDE_LEN+1];  
                   // include front and right edges of floor

//    for (int i = 0; i < SIDE_LEN+1; i++)
//      for (int j = 0; j < SIDE_LEN+1; j++)
//        heights[i][j] = 0.0f;

//    hmap.flatFill(0.1);
    hmap.clusterFill(0, 20, (short)50, (short)1);

//    hmap.walkerFilter(5,0);
//    hmap.walkerFilter(10,0);
//    hmap.walkerFilter(7,0);
//    hmap.walkerFilter(3,0);
//

//
//    for (int i = 0; i < 200; i++)
    for (int i = 0; i < 0; i++)
      hmap.faultingFilter(1, 1);
//

//    hmap.normalize(50, 0);
//    hmap.normalize(30, 0);
    float[][] heights = hmap.toFloatArray();  

    return heights;
  }  // end of makeHills()


  private void createGeometry() {
    // create (x,y,z) coordinates
    Point3f[] coords = createCoords();

    QuadArray plane = new QuadArray(coords.length, 
      GeometryArray.COORDINATES | GeometryArray.NORMALS); 

    plane.setCoordinates(0, coords);

    // generate normals
    NormalGenerator ng = new NormalGenerator(Math.toRadians(30));
    GeometryInfo gInfo = new GeometryInfo(plane);
    ng.generateNormals(gInfo);

    setGeometry(gInfo.getGeometryArray());
//    setGeometry(plane);
  }  // end of createGeometry()


  private Point3f[] createCoords()
  /* Create the (x,y,z) coordinates for the scene. The (x,z) 
     values run from -SIDE_LEN/2 to SIDE_LEN/2, centered on (0,0). Each
     vertex is 1 unit apart, so SIDE_LEN should be even.
     For each (x,z) value, createTile() creates for 4 coordinates for 
     a quad (tile).
  */
  {
    Point3f[] coords = new Point3f[SIDE_LEN*SIDE_LEN*4];   // since each tile has 4 coords
    int i = 0;
    for(int z=0; z <= SIDE_LEN-1; z++) {    // skip z's front row
      for(int x=0; x <= SIDE_LEN-1; x++) {  // skip x's right column
        createTile(coords, i, x, z);
        i = i + 4;  // since 4 coords created for 1 tile
      }
    }
    return coords;
  }  // end of createCoords()


  private void createTile(Point3f[] coords, int i, int x, int z)
  // Coords for a single quad (tile), its top left hand corner is at (x,height,z)
  {
    // (xc, zc) is the (x,z) coordinate in the scene
    float xc = x - SIDE_LEN / 2;
    float zc = z - SIDE_LEN / 2;

    // points created in counter-clockwise order from bottom left
    coords[i] = new Point3f(xc, heights[z+1][x], zc+1.0f);
    coords[i+1] = new Point3f(xc+1.0f, heights[z+1][x+1], zc+1.0f);
    coords[i+2] = new Point3f(xc+1.0f, heights[z][x+1], zc);
    coords[i+3] = new Point3f(xc, heights[z][x], zc);   
  }  // end of createTile()


  private void createAppearance() {
    Appearance app = new Appearance();

    // switch off face culling
    PolygonAttributes pa = new PolygonAttributes();
    pa.setCullFace(PolygonAttributes.CULL_NONE);
    app.setPolygonAttributes(pa);

    // shiny metal material (from Arms3D, Grabber.java)
    Color3f alumDiffuse = new Color3f(0.37f, 0.37f, 0.37f);
    Color3f black = new Color3f(0.0f, 0.0f, 0.0f);
    Color3f gray  = new Color3f(0.4f, 0.4f, 0.4f);
    Color3f blue  = new Color3f(0.0f, 0.0f, 1.0f);
    Color3f red   = new Color3f(1.0f, 0.0f, 0.0f);
    Color3f white = new Color3f(1.0f, 1.0f, 1.0f);
    Color3f alumSpecular = new Color3f(0.89f, 0.89f, 0.89f);

    Material mat = new Material(black, black, red, blue, 5);
       // sets ambient, emissive, diffuse, specular, shininess
    mat.setLightingEnable(true);
    app.setMaterial(mat);

    setAppearance(app);
  }  // end of createAppearance()
} // end of Landscape class
