package lavrin.hgen.viewer;

import java.awt.*;
import java.util.*;
import java.io.*;


public class ViewerProperties
{
  private static final String PROP_FNM = "viewer_props.txt";
  // where the property key=value pairs are stored
  private static final String RECIPE = "hmap.csv";

  private static final int PWIDTH = 640;
  private static final int PHEIGHT = 640;
  private static final int MIN_LEN = 200;

  private static final int UPDATE_TIME = 250;
  private static final int MIN_UPDATE_TIME = 150;

  private static final boolean FULLSCREEN = false;

  private Properties viewerProps;
  private Dimension screenDim;   // size of the screen


  public ViewerProperties()
  {
    loadProperties();
    listProperties();
    screenDim = Toolkit.getDefaultToolkit().getScreenSize();
  }


  private void loadProperties()
    // load the properties from the PROP_FNM file
  {
    viewerProps = new Properties();
    try {
      FileInputStream in = new FileInputStream(PROP_FNM);
      viewerProps.load(in);
      in.close();
      System.out.println("Loaded properties from " + PROP_FNM);
    } 
    catch (IOException e) {
      System.out.println("Could not load properties from " + PROP_FNM);
    }
  }


  private void listProperties()
  {
    if (viewerProps.isEmpty())
      System.out.println("No properties in " + PROP_FNM);
    else {
      System.out.println("Properties in " + PROP_FNM);
      viewerProps.list(System.out);
    }
  }


  public boolean isFullScreen()
    /* return the fullscreen string value (true or false)
       as a boolean; the default is false */
  {
    String prop;
    if ((prop = viewerProps.getProperty("fullscreen")) != null)
      return Boolean.valueOf(prop);
    else {
      System.out.printf("No 'fullscreen' property found; using %s\n", 
        (new Boolean(FULLSCREEN)).toString());
      return FULLSCREEN;
    }
  }


  public void setFullScreen(boolean b) {
    viewerProps.setProperty("fullscreen", Boolean.toString(b));
  }


  public int getWidth() {
    String prop;
    if ((prop = viewerProps.getProperty("width")) != null)
      return checkWidth(prop);
    else {
      System.out.println("No width property found; using " + PWIDTH);
      return PWIDTH;
    }
  }  // end of assignWidth()


  private int checkWidth(String widthStr)
    /* the width string must be an integer between MIN_LEN and the 
       screen's width */
  {
    int width = extractInt(widthStr);
    if (width < MIN_LEN) {
      System.out.println("width too small; set to " + MIN_LEN);
      return MIN_LEN;
    }
    else if (width > screenDim.width) {
      System.out.println("width too large; set to " + screenDim.width);
      return screenDim.width;
    }
    return width;
  }  // end of checkWidth()


  private int extractInt(String str)
    /* convert the string to an integer; the default value is -1 */
  {
    int num = -1;
    try {
      num = Integer.parseInt(str);
    }
    catch(NumberFormatException ex) {
      System.out.println("Error: " + str + " was not an integer");
    }
    return num;
  }  // end of extractInt()


  public void setWidth(String widthStr)
    /* store the appl. window width string (an integer)
       as a string. Check that the integer is valid. */
  {
    int width = checkWidth(widthStr);
    viewerProps.setProperty("width", ""+width);
  }  // end of setWidth()


  public int getHeight()
    /* return the appl. window height string value (an integer)
       as a valid integer; the default is PHEIGHT */
  {
    String prop;
    if ((prop = viewerProps.getProperty("height")) != null) {
      return checkHeight(prop);
    }
    else {
      System.out.println("No height property found; using " + PHEIGHT);
      return PHEIGHT;
    }
  }  // end of getHeight()


  private int checkHeight(String heightStr)
    /* the height string must be an integer between MIN_LEN and the 
       screen's height */
  {
    int height = extractInt(heightStr);
    if (height < MIN_LEN) {
      System.out.println("height too small; set to " + MIN_LEN);
      return MIN_LEN;
    }
    else if (height > screenDim.height) {
      System.out.println("height too large; set to " + screenDim.height);
      return screenDim.height;
    }
    return height;
  }  // end of checkHeight()


  public void setHeight(String heightStr)
    /* store the appl. window height string (an integer)
       as a string. Check that the integer is valid. */
  {
    int height = checkHeight(heightStr);
    viewerProps.setProperty("height", ""+height);
  }  // end of setHeight()


  public int getUpdateTime() {
    String prop;
    if ((prop = viewerProps.getProperty("update_time")) != null)
      return checkUpdateTime(prop);
    else {
      System.out.println("No update_time property found; using " + UPDATE_TIME);
      return UPDATE_TIME;
    }
  }


  private int checkUpdateTime(String widthStr) {
    int width = extractInt(widthStr);
    if (width < MIN_UPDATE_TIME) {
      System.out.println("update time too small; set to " + MIN_UPDATE_TIME);
      return MIN_UPDATE_TIME;
    }
    return width;
  }


  public void setUpdateTime(String sUpdateTime) {
    int updateTime = checkUpdateTime(sUpdateTime);
    viewerProps.setProperty("update_time", "" + updateTime);
  }


  public String getRecipe()
  {
    String prop;
    if ((prop = viewerProps.getProperty("recipe")) != null)
      return prop;
    else {
      System.out.println("No 'recipe' property found; using 'hmap.csv'");
      return "hmap.csv";
    }
  }


  public void setRecipe(String recipe)
  {
    viewerProps.setProperty("recipe", recipe);
  }


  public String getControls()
  {
    String prop;
    if ((prop = viewerProps.getProperty("controls")) != null) {
      if (! (prop.equals("mouse") || prop.equals("keys"))) {
        String err = 
          "Unknown 'controls' property value %s. Falling back to 'mouse'.\n";
        System.out.printf(err, prop);
        return "mouse";
      }
      return prop;
    } else {
      System.out.println("No 'controls' property found; using 'mouse'");
      return "mouse";
    }
  }


  public void setControls(String controls)
  {
    viewerProps.setProperty("controls", controls);
  }


  public void saveProperties()
    // save the properties to the PROP_FNM file
  {
    listProperties();

    try {
      FileOutputStream out = new FileOutputStream(PROP_FNM);
      viewerProps.store(out, "Properties");
      out.close();
      System.out.println("Saved properties in " + PROP_FNM);
    } 
    catch (IOException e) {
      System.out.println("Could not save properties in " + PROP_FNM);
    }
  }
}
