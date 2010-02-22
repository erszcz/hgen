package lavrin.hgen.viewer;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;

import lavrin.hgen.*;

public class Wedge extends Shape3D {
  private Geometry geo;
  private Appearance app;

  public Wedge() {
    geo = createGeometry();
    app = createAppearance();
    this.setGeometry(geo);
    this.setAppearance(app);
  }

  // code to create default geometry of visual object
  private Geometry createGeometry() {
    QuadArray qArr = new QuadArray(8, GeometryArray.COORDINATES
      | GeometryArray.NORMALS);

    qArr.setCoordinate(0, new Point3f(-10.0f,  0.0f, -10.0f));
    qArr.setCoordinate(1, new Point3f(-10.0f,  0.0f,  10.0f));
    qArr.setCoordinate(2, new Point3f(  0.0f, 10.0f,  10.0f));
    qArr.setCoordinate(3, new Point3f(  0.0f, 10.0f, -10.0f));

    qArr.setCoordinate(4, new Point3f(  0.0f, 10.0f, -10.0f));
    qArr.setCoordinate(5, new Point3f(  0.0f, 10.0f,  10.0f));
    qArr.setCoordinate(6, new Point3f( 10.0f,  0.0f,  10.0f));
    qArr.setCoordinate(7, new Point3f( 10.0f,  0.0f, -10.0f));

//    Vector3f nLeft  = new Vector3f( -5.0f,  2.0f,  0.0f);
//    Vector3f nRight = new Vector3f(  5.0f,  2.0f,  0.0f);
//    qArr.setNormal(0, nLeft);
//    qArr.setNormal(1, nLeft);
//    qArr.setNormal(2, nLeft);
//    qArr.setNormal(3, nLeft);
//    qArr.setNormal(4, nRight);
//    qArr.setNormal(5, nRight);
//    qArr.setNormal(6, nRight);
//    qArr.setNormal(7, nRight);
//
//    return qArr;

    NormalGenerator ng = new NormalGenerator(Math.toRadians(30));
    GeometryInfo gInfo = new GeometryInfo(qArr);
    ng.generateNormals(gInfo);

    return gInfo.getGeometryArray();
  }


  private static final Color3f black = new Color3f(0.0f, 0.0f, 0.0f);
  private static final Color3f gray  = new Color3f(0.4f, 0.4f, 0.4f);
  private static final Color3f blue  = new Color3f(0.0f, 0.0f, 1.0f);
  private static final Color3f red   = new Color3f(1.0f, 0.0f, 0.0f);
  private static final Color3f white = new Color3f(1.0f, 1.0f, 1.0f);


  // code to create default appearance of visual object
  private Appearance createAppearance () {
    Material mat = new Material(gray, black, blue, white, 100);

    PointAttributes pointAttrs = new PointAttributes();
    pointAttrs.setPointSize(10.0f);
    pointAttrs.setPointAntialiasingEnable(true);

    PolygonAttributes polyAttrs = new PolygonAttributes();
    polyAttrs.setBackFaceNormalFlip(true);
    polyAttrs.setCullFace(PolygonAttributes.CULL_NONE);
    polyAttrs.setPolygonMode(PolygonAttributes.POLYGON_LINE);

    Appearance app = new Appearance();
    app.setMaterial(mat);
    app.setPointAttributes(pointAttrs);
    app.setPolygonAttributes(polyAttrs);
    return app;
  }
}
