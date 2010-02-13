public class CHeightmap implements Heightmap
{
  public static void main (String[] args)
  {
    Heightmap hmap = new CHeightmap(10, 10);
    hmap.getHeight();
  }

  public CHeightmap(int height, int width) {
    this(height, width, 1);
  }

  public CHeightmap(int height, int width, int margin) {
    _peer = create(height, width, margin);
  }

  // Heightmap interface
  private boolean _wrap = true;
  public void setWrapped(boolean wrap) { _wrap = wrap; }
  public boolean isWrapped() { return _wrap; }

  public native int getHeight();
  public native int getWidth();
  public native int getMargin();
  public native double getPixel(int x, int y);
  public native double getMax();
  public native double getMin();

  public native boolean setPixel(int x, int y, double value);

  // fills
  public native void flatFill(double v);
  public native void randomFill(double min, double max);
  public native void clusterFill(double min, double max,
    short clusterChance, short radius);

  // filters
  public native void clusterFilter(int radius);
  public native void alternateClusterFilter(short radius);

  public void liquidFilter(double c, double d, double t, double u) {
    liquidFilter(c, d, t, u, _wrap);
  }
  private native void liquidFilter(double c, double d, double t, double u, boolean wrap);

  public void smoothFilter(short radius) {
    smoothFilter(radius, _wrap);
  }
  private native void smoothFilter(short radius, boolean wrap);

  public native void terraceFilter(short levels);

  public void walkerFilter(int incStep, int decStep) {
    walkerFilter(incStep, decStep, _wrap);
  }
  private native void walkerFilter(int incStep, int decStep, boolean wrap);

  public void faultingFilter(int incStep, int decStep) {
    faultingFilter(incStep, decStep);
  }
  private native void faultingFilter(int incStep, int decStep, boolean wrap);

  public native void normalize();
  public native void normalize(double max, double min);

  public native boolean hasMask();

  // native interface stuff
  private long _peer;  // pointer to native counterpart

  private native long create(int height, int width, int margin);
  private native void destroy(long peer);
  public void destroy()
  {
    destroy(_peer);
  }

  protected void finalize()
  {
    destroy();
  }

  static
  {
    System.loadLibrary("hmap");
  }
}
