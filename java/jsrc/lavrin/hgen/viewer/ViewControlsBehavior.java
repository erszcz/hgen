package lavrin.hgen.viewer;

// ViewControlsBehavior.java
// Andrew Davison, September 2006, ad@fivedots.coe.psu.ac.th

/* Use key presses to move the viewpoint.
   Movement is restricted to: forward, backwards, move left,
     move right, rotate left, rotate right, up, down.
   The down movement can not go below the starting height.

   The behaviour is added to the user's viewpoint. 
   It extends ViewPlatformBehavior so that targetTG is available
   to it, the ViewPlatform's tranform.
*/

import java.awt.AWTEvent;
import java.awt.event.*;
import java.util.Enumeration;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.behaviors.vp.*;



public class ViewControlsBehavior extends ViewPlatformBehavior
{
  private WakeupOnAWTEvent keyPress;
  private WakeupOnAWTEvent keyRelease;
  private WakeupOnElapsedFrames eachFrame;
  private WakeupCondition keyOrFrame;
  private static long prevTime = System.currentTimeMillis();
  private static long now = 0;

  // moves
  public static final int MOVE_FORWARD  = 0x0001;
  public static final int MOVE_BACKWARD = 0x0010;
  public static final int MOVE_LEFT     = 0x0100;
  public static final int MOVE_RIGHT    = 0x1000;

  private int move = 0;

//  private static final double ROT_AMT = Math.PI / 36.0;   // 5 degrees
  private static final double MOVE_STEP = 10.0;

  // hardwired movement vectors
  private static final Vector3d FORWARD   = new Vector3d(0,0,-MOVE_STEP);
  private static final Vector3d BACKWARD  = new Vector3d(0,0,MOVE_STEP);
  private static final Vector3d LEFT      = new Vector3d(-MOVE_STEP,0,0);
  private static final Vector3d RIGHT     = new Vector3d(MOVE_STEP,0,0);
//  private static final Vector3d UP = new Vector3d(0,MOVE_STEP,0);
//  private static final Vector3d DOWN = new Vector3d(0,-MOVE_STEP,0);

  // for repeated calcs
  private Transform3D t3d = new Transform3D();
  private Transform3D toMove = new Transform3D();
  private Transform3D toRot = new Transform3D();
  private Vector3d tran = new Vector3d();

//  private int upMoves = 0;


  public ViewControlsBehavior() {
    keyPress    = new WakeupOnAWTEvent(KeyEvent.KEY_PRESSED);
    keyRelease  = new WakeupOnAWTEvent(KeyEvent.KEY_RELEASED);
    eachFrame   = new WakeupOnElapsedFrames(0);
    keyOrFrame  = new WakeupOr(new WakeupCriterion[]{ keyPress,
      keyRelease, eachFrame });
  }


  public void initialize() {
    wakeupOn(keyOrFrame);
  }


  public void processStimulus(Enumeration criteria) {
    WakeupCriterion wakeup;

    while (criteria.hasMoreElements()) {
      wakeup = (WakeupCriterion)criteria.nextElement();
      if (wakeup instanceof WakeupOnAWTEvent) {
        AWTEvent[] event = ((WakeupOnAWTEvent)wakeup).getAWTEvent();
        for( int i = 0; i < event.length; i++ ) {
          if( event[i].getID() == KeyEvent.KEY_PRESSED ||
              event[i].getID() == KeyEvent.KEY_RELEASED) {
            processKeyEvent((KeyEvent)event[i]);
          }
        }
      } else if (wakeup instanceof WakeupOnElapsedFrames) {
        now = System.currentTimeMillis();
        doMove(now - prevTime);
        prevTime = now;
      }
    }
    wakeupOn(keyOrFrame);
  } // end of processStimulus()


  private void processKeyEvent(KeyEvent ev) {
    int keyCode = ev.getKeyCode();

    if (ev.getID() == KeyEvent.KEY_PRESSED) {
      System.out.println("Key pressed.");
      switch (keyCode) {
        case KeyEvent.VK_W: move |= MOVE_FORWARD;   break;
        case KeyEvent.VK_S: move |= MOVE_BACKWARD;  break;
        case KeyEvent.VK_A: move |= MOVE_LEFT;      break;
        case KeyEvent.VK_D: move |= MOVE_RIGHT;     break;
      }
    } else if (ev.getID() == KeyEvent.KEY_RELEASED) {
      System.out.println("Key released.");
      switch (keyCode) {
        case KeyEvent.VK_W: move ^= MOVE_FORWARD;   break;
        case KeyEvent.VK_S: move ^= MOVE_BACKWARD;  break;
        case KeyEvent.VK_A: move ^= MOVE_LEFT;      break;
        case KeyEvent.VK_D: move ^= MOVE_RIGHT;     break;
      }
    }
  }


//  private void rotateY(double radians)
//  // rotate about y-axis by radians
//  { targetTG.getTransform(t3d);   // targetTG is the ViewPlatform's transform
//    toRot.rotY(radians);
//    t3d.mul(toRot);
//    targetTG.setTransform(t3d);
//  }


  private void doMove(long timeDelta) {
    System.out.printf("move: %04x\n", move);
    if (move == 0) return;

    double factor = timeDelta * 0.001;

    tran.set(new double[]{ 0.0, 0.0, 0.0 });
    if ((move & MOVE_FORWARD) != 0)
      tran.add(FORWARD);
    if ((move & MOVE_BACKWARD) != 0)
      tran.add(BACKWARD);
    if ((move & MOVE_LEFT) != 0)
      tran.add(LEFT);
    if ((move & MOVE_RIGHT) != 0)
      tran.add(RIGHT);
    tran.scale(factor);

    targetTG.getTransform(t3d);
    toMove.setTranslation(tran);
    t3d.mul(toMove);
    targetTG.setTransform(t3d);
  }
}  // end of ViewControlsBehavior class
