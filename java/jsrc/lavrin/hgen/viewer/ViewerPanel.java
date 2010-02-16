package lavrin.hgen.viewer;

import javax.swing.*;
import java.awt.*;
import java.util.*;

import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.behaviors.vp.*;
import com.sun.j3d.utils.image.*;

//import lavrin.hgen.viewer.*;


public class ViewerPanel extends JPanel
{
  private static final int PWIDTH = 640;   // size of panel
  private static final int PHEIGHT = 640; 

  private static final int BOUNDSIZE = 500;  // larger than world

  private static final Point3d USERPOSN = new Point3d(0,10,30);
    // initial user position

  private static final int UPDATE_TIME = 100;  // ms, for updating the balls


  private SimpleUniverse su;
  private BranchGroup sceneBG;
  private BoundingSphere bounds;   // for environment nodes

  private float[][] heights;  // height map for the floor


  public ViewerPanel()
  {
    setLayout( new BorderLayout() );
    setOpaque( false );
    setPreferredSize( new Dimension(PWIDTH, PHEIGHT));

    GraphicsConfiguration config =
					SimpleUniverse.getPreferredConfiguration();
    Canvas3D canvas3D = new Canvas3D(config);
    add("Center", canvas3D);
    canvas3D.setFocusable(true);     // give focus to the canvas 
    canvas3D.requestFocus();

    su = new SimpleUniverse(canvas3D);

    reportTextureUnitInfo(canvas3D);
    createSceneGraph();
    initUserPosition();        // set user's viewpoint
    orbitControls(canvas3D);   // controls for moving the viewpoint
    
    su.addBranchGraph( sceneBG );
  } // end of ViewerPanel()



  private void reportTextureUnitInfo(Canvas3D c3d)
  /* Report the number of texture units supported by the machine's 
     graphics card. */
  {
    Map c3dMap = c3d.queryProperties();

    if (!c3dMap.containsKey("textureUnitStateMax"))
      System.out.println("Texture unit state maximum not found");
    else {
      int max  = ((Integer)c3dMap.get("textureUnitStateMax")).intValue();
      System.out.println("Texture unit state maximum: " + max);
    }
  }  // end of reportTextureUnitInfo()



  private void createSceneGraph() 
  // initilise the scene
  { 
    sceneBG = new BranchGroup();
    bounds = new BoundingSphere(new Point3d(0,0,0), BOUNDSIZE);   

    // depth-sort transparent objects on a per-geometry basis
    View view = su.getViewer().getView();
    view.setTransparencySortingPolicy(View.TRANSPARENCY_SORT_GEOMETRY);
    // adjust back clipping -- sight distance
    view.setBackClipDistance(100.0f);

    lightScene();         // the lights
    addBackground();      // the sky
    addFloor();           // the multi-textured floor (and splashes)

    sceneBG.compile();   // fix the scene
  } // end of createSceneGraph()


  private void lightScene()
  /* One ambient light, 2 directional lights */
  {
    Color3f white = new Color3f(1.0f, 1.0f, 1.0f);

    // Set up the ambient light
    // ambient light lights up every corner of the universe equally
    AmbientLight ambientLightNode = new AmbientLight(white);
    ambientLightNode.setInfluencingBounds(bounds);
    sceneBG.addChild(ambientLightNode);

    // directional lights
    // beams of these lights come from infinity, are parallel and directed dir -> 0,0,0
    Vector3f light1Direction  = new Vector3f(-1.0f, -1.0f, -1.0f);
       // left, down, backwards 
    Vector3f light2Direction  = new Vector3f(1.0f, -1.0f, 1.0f);
       // right, down, forwards

    DirectionalLight light1 = 
            new DirectionalLight(white, light1Direction);
    light1.setInfluencingBounds(bounds);
    sceneBG.addChild(light1);

    DirectionalLight light2 = 
        new DirectionalLight(white, light2Direction);
    light2.setInfluencingBounds(bounds);
    sceneBG.addChild(light2);
  }  // end of lightScene()



  private void addBackground()
  // A blue sky
  { Background back = new Background();
    back.setApplicationBounds( bounds );
    back.setColor(0.17f, 0.65f, 0.92f);    // sky colour
    sceneBG.addChild( back );
  }  // end of addBackground()


  private void addFloor()
  // the floor is a multi-textured mesh, with splashes of extra textures
  {
    Landscape floor = new Landscape();

    /* Start building an ordered group of floor meshes.
       Ordering avoids rendering conflicts between the meshes. */
    OrderedGroup floorOG = new OrderedGroup();
    floorOG.addChild(floor);

    // add all the meshes to the scene
    sceneBG.addChild( floorOG );

    TimeBehavior tb = new TimeBehavior(UPDATE_TIME, floor);
    tb.setSchedulingBounds(bounds);
    sceneBG.addChild(tb);
  }  // end of addFloor()



  private void orbitControls(Canvas3D c)
  /* OrbitBehaviour allows the user to rotate around the scene, and to
     zoom in and out.  */
  {
    OrbitBehavior orbit = 
		new OrbitBehavior(c, OrbitBehavior.REVERSE_ALL);
    orbit.setSchedulingBounds(bounds);

    ViewingPlatform vp = su.getViewingPlatform();
    vp.setViewPlatformBehavior(orbit);	 
  }  // end of orbitControls()


  private void initUserPosition()
  // Set the user's initial viewpoint using lookAt()
  {
    ViewingPlatform vp = su.getViewingPlatform();
    TransformGroup steerTG = vp.getViewPlatformTransform();

    Transform3D t3d = new Transform3D();
    steerTG.getTransform(t3d);

    // args are: viewer posn, where looking, up direction
    t3d.lookAt( USERPOSN, new Point3d(0,0,0), new Vector3d(0,1,0));
    t3d.invert();

    steerTG.setTransform(t3d);
  }  // end of initUserPosition()
} // end of ViewerPanel class
