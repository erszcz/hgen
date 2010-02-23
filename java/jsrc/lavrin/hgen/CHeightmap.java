package lavrin.hgen;

import java.io.*;

public class CHeightmap implements Heightmap
{
  public static void main (String[] args)
  {
    // initialize map
    Heightmap hm = new CHeightmap(10, 10);
    System.out.printf("Height, width, margin: %d, %d, %d\n",
      hm.getHeight(), hm.getWidth(), hm.getMargin());

    // fill and process
    hm.flatFill(50);
    for (int i = 0; i < 5; i++)
      hm.walkerFilter(10, 10);
    hm.normalize();

    ((CHeightmap)hm).saveAsText("dump10x10.txt");
  }

  public float[][] toArray() {
    int w = getWidth();
    int h = getHeight();
    float[][] map = new float[h][w];
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        map[i][j] = getPixel(i, j);
    return map;
  }

  // for testing
  public void saveAsText(String fname) {
    try {
      PrintStream out = new PrintStream(fname);
      for (int i = 0; i < getHeight(); i++)
      {
        for (int j = 0; j < getWidth(); j++)
          out.printf("%6.2f", getPixel(i, j));
        out.println();
      }
      out.close();
    } catch (FileNotFoundException e) {
      System.err.printf("Can't create/write file: %s\n", fname);
    }
  }

  public CHeightmap(int height, int width) {
    this(height, width, 1);
  }

  public CHeightmap(int height, int width, int margin) {
    this(height, width, margin, 0);
  }

  private CHeightmap(int height, int width, int margin, long peer) {
    if (peer == 0)
      _peer = create(height, width, margin);
    else
      _peer = peerCopy(peer);
    if (_peer == 0)
      throw new RuntimeException("can't create native instance");
  }

  // Heightmap interface
  private boolean _wrap = true;
  public void setWrapped(boolean wrap) { _wrap = wrap; }
  public boolean isWrapped() { return _wrap; }

  public native int getHeight();
  public native int getWidth();
  public native int getMargin();
  public native float getPixel(int x, int y);
  public native float getMax();
  public native float getMin();

  public native boolean setPixel(int x, int y, float value);

  // fills
  public native void flatFill(float v);
  public native void randomFill(float min, float max);
  public native void clusterFill(float min, float max,
    int clusterChance, int radius);

  // filters
  public native void clusterFilter(int radius);
  public native void alternateClusterFilter(int radius);

  public void liquidFilter(float c, float d, float t, float u) {
    liquidFilter(c, d, t, u, _wrap);
  }
  private native void liquidFilter(float c, float d, float t, float u, boolean wrap);

  public void smoothFilter(int radius) {
    smoothFilter(radius, _wrap);
  }
  private native void smoothFilter(int radius, boolean wrap);

  public native void terraceFilter(int levels);

  public void walkerFilter(int incStep, int decStep) {
    walkerFilter(incStep, decStep, _wrap);
  }
  private native void walkerFilter(int incStep, int decStep, boolean wrap);

  public void faultingFilter(int incStep, int decStep) {
    faultingFilter(incStep, decStep, _wrap);
  }
  private native void faultingFilter(int incStep, int decStep, boolean wrap);

  public native void normalize();
  public native void normalize(float max, float min);

  public void scale(float scale) {
    for (int i = 0; i < getHeight(); i++)
      for (int j = 0; j < getWidth(); j++)
        setPixel(i, j, getPixel(i, j) * scale);
  }

  public native boolean isMasked();

  // native interface stuff
  private long _peer;  // pointer to native counterpart

  private static native boolean initIDs();

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

  // get a native object copy using its copy constructor
  private native long peerCopy(long peer);

  public Heightmap copy() {
    return new CHeightmap(getWidth(), getHeight(), getMargin(), _peer);
  }

  static
  {
    System.loadLibrary("hmap");
    if (! initIDs())
      throw new RuntimeException("can't get native object address");
  }
}
