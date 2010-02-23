package lavrin.hgen.viewer;

import java.awt.AWTEvent;
import java.awt.event.*;
import java.util.Enumeration;
import javax.swing.Timer;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.behaviors.vp.*;



public class UserControlsBehavior extends ViewPlatformAWTBehavior
  implements ActionListener
{
  private static long prevTime = 0;
  private static long now = 0;

  // keyReleased bug workaround
  private final Timer timer;
  private boolean released = false;
  private KeyEvent releasedEvent;

  // moves
  public static final int MOVE_FORWARD  = 0x00000001;
  public static final int MOVE_BACKWARD = 0x00000010;
  public static final int MOVE_LEFT     = 0x00000100;
  public static final int MOVE_RIGHT    = 0x00001000;
  public static final int MOVE_UP       = 0x00010000;
  public static final int MOVE_DOWN     = 0x00100000;
  public static final int ROT_LEFT      = 0x01000000;
  public static final int ROT_RIGHT     = 0x10000000;

  private int move = 0;

  private static final double ROT_SPEED   = 0.6 * Math.PI; // rad
  private static final double MOVE_SPEED  = 25.0;

  // hardwired movement vectors
  private static final Vector3d FORWARD   = new Vector3d(0,0,-MOVE_SPEED);
  private static final Vector3d BACKWARD  = new Vector3d(0,0,MOVE_SPEED);
  private static final Vector3d LEFT      = new Vector3d(-MOVE_SPEED,0,0);
  private static final Vector3d RIGHT     = new Vector3d(MOVE_SPEED,0,0);
  private static final Vector3d UP        = new Vector3d(0,MOVE_SPEED,0);
  private static final Vector3d DOWN      = new Vector3d(0,-MOVE_SPEED,0);

  // for repeated calcs
  private Transform3D t3d     = new Transform3D();
  private Transform3D toMove  = new Transform3D();
  private Transform3D toRot   = new Transform3D();

  private Matrix3d rot        = new Matrix3d();
  private Vector3d tran       = new Vector3d();


  public UserControlsBehavior(Canvas3D c) {
    this(c, 0);
  }

  public UserControlsBehavior(Canvas3D c, int flags) {
//    super(ViewPlatformAWTBehavior.KEY_LISTENER | flags);
    super(c, ViewPlatformAWTBehavior.KEY_LISTENER | flags);
    timer = new Timer(1, this);
    motion = true;
    prevTime = System.currentTimeMillis();
  }


  public void keyPressed(KeyEvent ev) {
    released = false;
    timer.stop();

    setMoveOn(ev.getKeyCode());
  }


  public void keyReleased(KeyEvent ev) {
    if (! released) {
      releasedEvent = ev;
      timer.restart();
      return;
    }
    // real released event handling goes here

    setMoveOff(ev.getKeyCode());
  }


  private void setMoveOn(int keyCode) {
    switch (keyCode) {
      case KeyEvent.VK_W: move |= MOVE_FORWARD;   break;
      case KeyEvent.VK_S: move |= MOVE_BACKWARD;  break;
      case KeyEvent.VK_A: move |= MOVE_LEFT;      break;
      case KeyEvent.VK_D: move |= MOVE_RIGHT;     break;
      case KeyEvent.VK_X: move |= MOVE_UP;        break;
      case KeyEvent.VK_C: move |= MOVE_DOWN;      break;
      case KeyEvent.VK_Q: move |= ROT_LEFT;       break;
      case KeyEvent.VK_E: move |= ROT_RIGHT;      break;
    }
  }


  private void setMoveOff(int keyCode) {
    switch (keyCode) {
      case KeyEvent.VK_W: move ^= MOVE_FORWARD;   break;
      case KeyEvent.VK_S: move ^= MOVE_BACKWARD;  break;
      case KeyEvent.VK_A: move ^= MOVE_LEFT;      break;
      case KeyEvent.VK_D: move ^= MOVE_RIGHT;     break;
      case KeyEvent.VK_X: move ^= MOVE_UP;        break;
      case KeyEvent.VK_C: move ^= MOVE_DOWN;      break;
      case KeyEvent.VK_Q: move ^= ROT_LEFT;       break;
      case KeyEvent.VK_E: move ^= ROT_RIGHT;      break;
    }
  }


  public void actionPerformed(ActionEvent e) {
    released = true;
    timer.stop();
    keyReleased(releasedEvent);
  }


  protected synchronized void processAWTEvents(AWTEvent[] events) {
    for (AWTEvent ev : events) {
      if (ev.getID() == KeyEvent.KEY_PRESSED)
        keyPressed((KeyEvent)ev);
      else if (ev.getID() == KeyEvent.KEY_RELEASED)
        keyReleased((KeyEvent)ev);
    }
  }


  protected synchronized void integrateTransforms() {
    now = System.currentTimeMillis();
    float timeDelta = now - prevTime;
    prevTime = now;

    System.out.printf("move: %06x\n", move);
    if (move == 0) return;

    float factor = timeDelta * 0.001f;

    targetTG.getTransform(t3d);
    t3d.get(rot, tran);

    tran.set(0.0, 0.0, 0.0);
    if ((move & MOVE_FORWARD) != 0)
      tran.add(FORWARD);
    if ((move & MOVE_BACKWARD) != 0)
      tran.add(BACKWARD);
    if ((move & MOVE_LEFT) != 0)
      tran.add(LEFT);
    if ((move & MOVE_RIGHT) != 0)
      tran.add(RIGHT);
    if ((move & MOVE_UP) != 0)
      tran.add(UP);
    if ((move & MOVE_DOWN) != 0)
      tran.add(DOWN);
    tran.scale(factor);

    toMove.setTranslation(tran);
    t3d.mul(toMove);

    System.out.println("asd");
    toRot.set(rot);
    if ((move & ROT_LEFT) != 0)
      toRot.rotY( ROT_SPEED * factor);
    if ((move & ROT_RIGHT) != 0)
      toRot.rotY(-ROT_SPEED * factor);

    if ((move & (ROT_LEFT | ROT_RIGHT)) != 0)
      t3d.mul(toRot);
    System.out.println("qwe");

    targetTG.setTransform(t3d);
  }
}  // end of UserControlsBehavior class
