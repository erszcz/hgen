package lavrin.hgen.viewer;

import java.util.*;
import java.util.Enumeration;
import javax.media.j3d.*;


public class TimeBehavior extends Behavior
{
  private WakeupCondition timeOut;
  private Landscape landscape;

  public TimeBehavior(int timeDelay, Landscape lscape) {
    timeOut = new WakeupOnElapsedTime(timeDelay);
    landscape = lscape;
  }

  public void initialize() {
    wakeupOn(timeOut);
  }

  public void processStimulus(Enumeration criteria) {
    landscape.update();
    wakeupOn(timeOut);
  } // end of processStimulus()
}  // end of TimeBehavior class
