package lavrin.hgen.viewer;

import javax.swing.*;
import java.awt.*;
import java.util.*;

import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.behaviors.keyboard.*;
import com.sun.j3d.utils.behaviors.vp.*;
import com.sun.j3d.utils.image.*;

import lavrin.hgen.viewer.*;


public class ViewerPanel extends JPanel
{
  private static final int PWIDTH = 640;   // size of panel
  private static final int PHEIGHT = 640; 

  private static final int BOUNDSIZE = 500;  // larger than world

  private final static float Z_START = 200.0f;

  private static final int UPDATE_TIME = 250;  // ms, for updating the balls

  private Canvas3D canvas3D;

  private SimpleUniverse su;
  private BranchGroup sceneBG;
  private BoundingSphere bounds;   // for environment nodes


  public ViewerPanel()
  {
    setLayout( new BorderLayout() );
    setOpaque( false );
    setPreferredSize( new Dimension(PWIDTH, PHEIGHT));

    GraphicsConfiguration config =
					SimpleUniverse.getPreferredConfiguration();
    canvas3D = new Canvas3D(config);
    add("Center", canvas3D);
    canvas3D.setFocusable(true);     // give focus to the canvas 
    canvas3D.requestFocus();

    su = new SimpleUniverse(canvas3D);

    createSceneGraph();
    createUserControls();

    sceneBG.compile();

    su.addBranchGraph( sceneBG );
  } // end of ViewerPanel()


  private void createSceneGraph() 
  // initialize the scene
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
    addLandscape();       // the multi-textured land (and splashes)
//    addSphere();
    addWedge();

    sceneBG.compile();   // fix the scene
  } // end of createSceneGraph()


  private void lightScene()
  /* One ambient light, 2 directional lights */
  {
    Color3f twilight = new Color3f(0.1f, 0.2f, 0.2f);
    Color3f white = new Color3f(1.0f, 1.0f, 1.0f);
    Color3f blue  = new Color3f(0.0f, 0.0f, 1.0f);

    // Set up the ambient light
    // ambient light lights up every corner of the universe equally
//    AmbientLight ambLight = new AmbientLight(twilight);
    AmbientLight ambLight = new AmbientLight(white);
    ambLight.setInfluencingBounds(bounds);
    sceneBG.addChild(ambLight);

    // directional lights
    // beams of these lights come from infinity, are parallel
    // and pointed at origin
    DirectionalLight dirLight1 = new DirectionalLight(white,
      /* direction: */ new Vector3f( 20.0f, 5.0f, 0.0f));
    dirLight1.setInfluencingBounds(bounds);
    sceneBG.addChild(dirLight1);

    DirectionalLight dirLight2 = new DirectionalLight(blue,
      /* direction: */ new Vector3f(0.0f, 10.0f, -10.0f));
    dirLight2.setInfluencingBounds(bounds);
    sceneBG.addChild(dirLight2);

    DirectionalLight dirLight3 = new DirectionalLight(white,
      /* direction: */ new Vector3f(-20.0f, 4.0f, 0.0f));
    dirLight3.setInfluencingBounds(bounds);
    sceneBG.addChild(dirLight3);

    DirectionalLight dirLight4 = new DirectionalLight(white,
      /* direction: */ new Vector3f(0.0f, 7.0f, 10.0f));
    dirLight4.setInfluencingBounds(bounds);
    sceneBG.addChild(dirLight4);
  }  // end of lightScene()



  private void addBackground() {
    Background back = new Background();
    back.setApplicationBounds( bounds );
//    back.setColor(0.17f, 0.65f, 0.92f);    // sky colour
    back.setColor(0.65f, 0.65f, 0.42f);    // sky colour
    sceneBG.addChild( back );
  }  // end of addBackground()


  private void addLandscape() {
    Landscape land = new Landscape();

    sceneBG.addChild(land);

    TimeBehavior tb = new TimeBehavior(UPDATE_TIME, land);
    tb.setSchedulingBounds(bounds);
    sceneBG.addChild(tb);
  }  // end of addLandscape()


  private void addSphere() {
    // add sphere to check shading
    Color3f white = new Color3f(1.0f, 1.0f, 1.0f);
    Color3f blue  = new Color3f(0.0f, 0.0f, 1.0f);
    Color3f red   = new Color3f(1.0f, 0.0f, 0.0f);
    Color3f black = new Color3f(0.0f, 0.0f, 0.0f);

    Appearance spApp = new Appearance();
    Material spMat = new Material(black, black, red, blue, 5);
    spApp.setMaterial(spMat);
    Sphere sp = new Sphere(10.0f, Primitive.GENERATE_NORMALS, spApp);
    Transform3D pos = new Transform3D();
    pos.set(new Vector3f(0, 10, 0));
    TransformGroup spTG = new TransformGroup(pos);
    spTG.addChild(sp);

    sceneBG.addChild(spTG);
  }


  private void addWedge() {
    // position
    Transform3D pos = new Transform3D();
    pos.set(new Vector3f(1, 2, 0));
    TransformGroup wedgeTG = new TransformGroup(pos);

    // object
    Wedge wedge = new Wedge();

    wedgeTG.addChild(wedge);
    sceneBG.addChild(wedgeTG);
  }


  private void createUserControls() { 
    ViewingPlatform vp = su.getViewingPlatform();

    // position viewport
    TransformGroup targetTG = vp.getViewPlatformTransform();
    Transform3D t3d = new Transform3D();
    targetTG.getTransform(t3d);
    t3d.setTranslation( new Vector3d(0,1,Z_START));
    targetTG.setTransform(t3d);

    // set up keyboard controls to move the viewport
    ViewPlatformBehavior controlBehavior = new UserControlsBehavior(canvas3D);
//    ViewPlatformBehavior controlBehavior = new OrbitBehavior();
    controlBehavior.setSchedulingBounds(bounds);
    vp.setViewPlatformBehavior(controlBehavior);
  }
} // end of ViewerPanel class
