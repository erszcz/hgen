interface Heightmap
{
  public void setWrapped(boolean wrap);
  public boolean isWrapped();

  public int getHeight();
  public int getWidth();
  public int getMargin();
  public double getPixel(int x, int y);
  public double getMax();
  public double getMin();

  public boolean setPixel(int x, int y, double value);

  public void flatFill(double v);
  public void randomFill(double min, double max;

  public void clusterFill(double min, double max,
    short clusterChance, short radius);

  public void clusterFilter(int radius);

  public void alternateClusterFilter(short radius);

  public void liquidFilter(double c, double d, double t, double u);

  public void smoothFilter(short radius);
  public void terraceFilter(short levels);

  public void walkerFilter(int incStep, int decStep);

  public void faultingFilter(int incStep, int decStep);

  public void normalize();
  public void normalize(double max, double min);

  public boolean hasMask();
}

public class NativeHeightmap implements Heightmap
{
  public NativeHeightmap(int height, int width) {
    super(height, width, 1);
  }

  public NativeHeightmap(int height, int width, int margin) {
    peer = create(height, width, margin);
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
  public native void randomFill(double min, double max;
  public native void clusterFill(double min, double max,
    short clusterChance, short radius);

  // filters
  public void clusterFilter(int radius);
  public void alternateClusterFilter(short radius);

  public void liquidFilter(double c, double d, double t, double u) {
    liquidFilter(c, d, t, u, _wrap);
  }
  private native void liquidFilter(double c, double d, double t, double u, boolean wrap);

  public void smoothFilter(short radius) {
    smoothFilter(radius, _wrap);
  }
  private native void smoothFilter(short radius);

  public native void terraceFilter(short levels);

  public void walkerFilter(int incStep, int decStep) {
    walkerFilter(incStep, decStep, _wrap);
  }
  private native void walkerFilter(int incStep, int decStep);

  public void faultingFilter(int incStep, int decStep) {
    faultingFilter(incStep, decStep);
  }
  private native void faultingFilter(int incStep, int decStep);

  public void normalize();
  public void normalize(double max, double min);

  public boolean hasMask();

  // native interface stuff
  private long _peer;  // pointer to native counterpart

  private native long create(int height, width, margin);
  private native void destroy(long peer);
  public destroy()
  {
    destroy(peer);
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
