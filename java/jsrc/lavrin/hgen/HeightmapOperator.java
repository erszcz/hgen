package lavrin.hgen;

/*
  Feed line format - CSV:

    qty, operationName, arg1, arg2, ..., argN

  Lines starting with '#' are treated as comments and ignored.
  Empty lines are ignored.

  Allowed separators: ',', '<tab>', '<space>'.
  Each may be surounded by any number of whitespace.

  Allowed operations are those supported by the Heightmap interface:
    - *Fill, *Filter,
    - normalize, normalize(max, min), scale(scale), setPixel(x,y,val),
    - initialize(width, height, margin) -- this operation
      is for recipes used straight for Operator class constructor,
      it's ignored by further load calls (thanks to that there's no need
      to read the recipe file before creating an operator object to obtain
      the parameters for Hegightmap creation).
      This operation must come on the first input line (comments are ignored).
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import lavrin.hgen.CHeightmap;
import lavrin.hgen.Heightmap;

public class HeightmapOperator {
  public static void main (String[] args)
  {
    try {
      HeightmapOperator hop = new HeightmapOperator("recipe.csv");
      hop.commit();
      hop.save("recipe_bak.csv");
      hop.getHeightmap().saveAsText("recipe_hmap_dump.txt");
    } catch (HeightmapUninitializedException e) {
      e.printStackTrace();
    }
  }


  private Heightmap hmap;
  private List<Map<String, Object>> pending;
  private List<Map<String, Object>> history;
  private boolean initialized = false;


  public HeightmapOperator(int width, int height, int margin) {
    pending = new ArrayList<Map<String, Object>>();
    history = new ArrayList<Map<String, Object>>();

    initialize(width, height, margin);

    // register operation
    Map<String, Object> init = new HashMap<String, Object>(3);
    init.put("qty", 1);
    init.put("name", "initialize");
    init.put("args", Arrays.asList(new int[]{width, height, margin}));
    history.add(init);
  }


  public HeightmapOperator(String filename)
    throws HeightmapUninitializedException 
  {
    pending = new ArrayList<Map<String, Object>>();
    history = new ArrayList<Map<String, Object>>();
    load(filename);

    if (! initFromFilePossible()) {
      String errMsg = String.format("no Heightmap initialization data" + 
        "- insert at the beginning of recipe file %s", filename);
      throw new HeightmapUninitializedException(errMsg);
    } else // initFromFilePossible
      step();
        // first pending operation should be 'initialize' -- step will call
        // the suitable method and register the operation in history
  }


  private void initialize(int width, int height, int margin) {
    hmap = new CHeightmap(width, height, margin);
    initialized = true;
  }


  // called after load in 'from file' constructor
  // 'initialize' present in recipe ? return true : return false
  private boolean initFromFilePossible() {
    // check for Heightmap initialization information
    try {
      // initOp -- 'initialize' operation
      Map initOp = (Map)pending.get(0);
        // initOp ought to be the first operation in recipe
        // as specified at the beginning of this file
      if (initOp.get("name").equals("initialize"))
        return true;
//      {
//        List args = (List)initOp.get("args");
//        hmap = new CHeightmap(
//          (Integer)args.get(0),
//          (Integer)args.get(1),
//          (Integer)args.get(2)
//        );
//        initialized = true;
    } catch (IndexOutOfBoundsException e) {
      return false;
    } catch (ClassCastException e) {
      return false;
    }
    return false;
  }


  /**
    Load Heightmap generation recipe from CSV file.
    Loaded entries are appended to the queue of pending operations.
  */
  public void load(String filename) {
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(
        new FileInputStream(filename)));
      String s;
      while ( (s = br.readLine()) != null) {
        if (s.startsWith("#") || s.isEmpty()) continue;
        
        String[] tokens = s.split("[\\s,]*");
        Map<String, Object> m = new HashMap<String, Object>(3);
        m.put("qty", Integer.parseInt(tokens[0]));
        m.put("name", tokens[1]);

        List args = new ArrayList();
        for (int i = 2; i < tokens.length; i++)
          args.add(tokens[i]);

        m.put("args", args); // even empty list is put into the map

        pending.add(m);
      }
    } catch (IOException e) {
      e.printStackTrace();
    } catch (IndexOutOfBoundsException e) {
      // this mustn't happen
      e.printStackTrace();
    }
  }


  // TODO: save history
  /**
    Save operation history as CSV recipe file.
    All operations performed since initialization are written
    down with their exact quantity, parameters and in the order of applying
    to the Heightmap.
  */
  public void save(String filename) {
    for (Map m : history) {

    }
  }


  /**
    Return the Heightmap instance the operator manipulates on.
  */
  public Heightmap getHeightmap() {
    return hmap;
  }


  /**
    Perform one operation from the queue.
    One operation means one single procedure call to the Heightmap, i.e.
    if there are following operations pending:

      - 2,faultingFilter,10.0,5.0
      - 3,smoothFilter,1

    then only one faultingFiltering is performed. Resulting operation queue is:

      - 1,faultingFilter,10.0,5.0
      - 3,smoothFilter,1.
  */
  public void step() /*throws InvalidOperationException*/ {
    if (pending.isEmpty()) return;

    Map<String, Object> op = pending.get(0);
    int qty = (Integer)op.get("qty");
    String name = (String)op.get("name");
    List args = (List)op.get("args");

    if (name.equals("initialize")) {
      if (initialized) return;

      initialize( new Integer(args.get(0)),
        new Integer(args.get(1)), new Integer(args.get(2)) );
      history.add(op);
      return;
    }

    // TODO: when operation is not 'initialize'
  }


  /**
    Carry out all pending operations.
  */
  public void commit() {
    while (! pending.isEmpty())
      step();
  }
}

class HeightmapOperatorException extends Exception {
  public HeightmapOperatorException(String message) {
    super(message);
  }
}

class HeightmapUninitializedException extends HeightmapOperatorException {
  public HeightmapUninitializedException(String message) {
    super(message);
  }
}

class RecipeParseException extends HeightmapOperatorException {
  public RecipeParseException(String message) {
    super(message);
  }
}

class InvalidOperationException extends HeightmapOperatorException {
  public InvalidOperationException(String message) {
    super(message);
  }
}
