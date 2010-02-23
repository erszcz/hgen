package lavrin.hgen;

public interface Heightmap
{
  public void setWrapped(boolean wrap);
  public boolean isWrapped();

  public int getHeight();
  public int getWidth();
  public int getMargin();
  public float getPixel(int x, int y);
  public float getMax();
  public float getMin();

  public boolean setPixel(int x, int y, float value);

  public void flatFill(float v);
  public void randomFill(float min, float max);

  public void clusterFill(float min, float max,
    int clusterChance, int radius);

  public void clusterFilter(int radius);

  public void alternateClusterFilter(int radius);

  public void liquidFilter(float c, float d, float t, float u);

  public void smoothFilter(int radius);
  public void terraceFilter(int levels);

  public void walkerFilter(int incStep, int decStep);

  public void faultingFilter(int incStep, int decStep);

  public void normalize();
  public void normalize(float max, float min);

  public void scale(float scale);

  public boolean isMasked();

  public float[][] toArray();

  public Heightmap copy();
}
