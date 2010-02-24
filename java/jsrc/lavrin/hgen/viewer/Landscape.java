package lavrin.hgen.viewer;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;

import lavrin.hgen.*;

public class Landscape extends Shape3D 
{
//  private final static int SIDE_LEN = 256;
    /* Should be even, since the code assumes that SIDE_LEN/2 is 
       a whole number. */
//  private final static int MARGIN = SIDE_LEN / 8;
  private int SIDE_LEN;
  private int MARGIN;

  private Heightmap hmap;
  private HeightmapOperator hop;

  public Landscape() {
    setCapability(ALLOW_GEOMETRY_READ);
    setCapability(ALLOW_GEOMETRY_WRITE);

//    hmap = new CHeightmap(SIDE_LEN + 1, SIDE_LEN + 1, MARGIN);
//    hmap.setWrapped(false);
    initHeightmap();

    createGeometry();
    createAppearance();
  } // end of Landscape()

  private void initHeightmap() {
//    hmap.flatFill(0.0f);
//    hmap.clusterFill(0, 100, 50, MARGIN / 2);
//    hmap.walkerFilter(5, 15);
//    hmap.walkerFilter(7, 2);

//    hmap.walkerFilter(1, 1);
//    hmap.smoothFilter(MARGIN);
//    hmap.smoothFilter(1);

//    for (int i = 0; i < 100; i++)
//      hmap.faultingFilter(10,5);
//    hmap.smoothFilter(MARGIN / 3);
//    hmap.walkerFilter(1, 1);
//    hmap.smoothFilter(1);

//    HeightmapOperator hop =
//      new HeightmapOperator(SIDE_LEN + 1, SIDE_LEN + 1, MARGIN);
//    hop.load("hmap2_in.csv");
//    hop.commit();
//    hmap = hop.getHeightmap();

    try {
      hop = new HeightmapOperator("viewer_in.csv");
//      hop.commit();
      hmap = hop.getHeightmap();
      SIDE_LEN = hmap.getWidth();
      MARGIN = hmap.getMargin();
    } catch (Exception e) {
      e.printStackTrace();
      hmap = new CHeightmap(SIDE_LEN + 1, SIDE_LEN + 1, MARGIN);
    }
  }

  public void update() {
//    hmap.smoothFilter(MARGIN / 3);
    hop.step();
    createGeometry();
  }


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
  }  // end of createGeometry()


  private Point3f[] createCoords() {
    Point3f[] coords = new Point3f[SIDE_LEN*SIDE_LEN*4];
      // since each tile has 4 coords
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

    float min = hmap.getMin();
    float max = hmap.getMax();
    float scale = 70.0f;

    // points created in counter-clockwise order from bottom left
    coords[i]   = new Point3f(xc, getNS(z+1, x, min, max, scale), zc + 1.0f);
    coords[i+1] = new Point3f(xc + 1.0f, getNS(z+1, x+1, min, max, scale), zc + 1.0f);
    coords[i+2] = new Point3f(xc + 1.0f, getNS(z, x+1, min, max, scale), zc);
    coords[i+3] = new Point3f(xc, getNS(z, x, min, max, scale), zc);
  }  // end of createTile()

  // return normalized and scaled value of heightmap at x, y
  private float getNS(int x, int y, float min, float max, float scale)
  {
    return (hmap.getPixel(x, y) - min) / (max - min) * scale;
  }


  private void createAppearance() {
    Appearance app = new Appearance();

    // switch off face culling
    PolygonAttributes pa = new PolygonAttributes();
    pa.setCullFace(PolygonAttributes.CULL_NONE);
    app.setPolygonAttributes(pa);

    Color3f black     = new Color3f(0.0f, 0.0f, 0.0f);
    Color3f gray      = new Color3f(0.1f, 0.1f, 0.1f);
    Color3f blue      = new Color3f(0.0f, 0.0f, 1.0f);
    Color3f navy      = new Color3f(0.0f, 0.0f, 0.1f);
    Color3f darkBrown = new Color3f(0.1f, 0.03f, 0.0f);
    Color3f red       = new Color3f(1.0f, 0.0f, 0.0f);
    Color3f brown     = new Color3f(0.7f, 0.2f, 0.0f);
    Color3f white     = new Color3f(1.0f, 1.0f, 1.0f);

    Material mat = new Material(darkBrown, black, brown, blue, 45);
      // sets ambient, emissive, diffuse, specular, shininess
    mat.setLightingEnable(true);
    app.setMaterial(mat);

    setAppearance(app);
  }  // end of createAppearance()
} // end of Landscape class
