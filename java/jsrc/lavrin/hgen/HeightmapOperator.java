package lavrin.hgen;

/*
  Feed line format - CSV:

    qty, operationName, arg1, arg2, ..., argN

  Lines starting with '#' are treated as comments and ignored.
  Empty lines are ignored.

  Allowed separators: ',', '<tab>'.
  Each may be surounded by any number of whitespace.

  Allowed operations are those supported by the Heightmap interface:
    - *Fill, *Filter,
    - normalize, *no* normalize(max, min), scale(scale), setPixel(x,y,val)
      -- the limitation concerning overloaded normalize stems from too
      much hassle required to allow for it (maybe someday)
    - initialize(width, height, margin) -- this operation
      is for recipes used straight for Operator class constructor,
      it's ignored by further load calls (thanks to that there's no need
      to read the recipe file before creating an operator object to obtain
      the parameters for Hegightmap creation).
      This operation must come on the first input line (comments are ignored).
*/

// TODO:
//  - Create HeightmapOperation class for history/pending lists.
//    The Map<String, Object> construct used now has specific structure
//    and some conventions which must be preserved when handling it and they
//    may be easily broken or forgotten.
//  - exceptions in 'load'
//  - operations different than 'initialize' in 'step'

import java.io.*;
import java.lang.reflect.*;
import java.util.*;

import lavrin.hgen.CHeightmap;
import lavrin.hgen.Heightmap;

public class HeightmapOperator {
  public static void main (String[] args)
  {
    try {
      HeightmapOperator hop = new HeightmapOperator("hmap1_in.csv");
      hop.commit();
      hop.save("hmap1_recipe.csv");
      hop.getHeightmap().saveAsText("hmap1_dump.txt");


      HeightmapOperator hop2 = new HeightmapOperator(9, 9, 1);
    } catch (HeightmapUninitializedException e) {
      e.printStackTrace();
    }
  }


  private Heightmap hmap;
  private List<Map<String, Object>> pending;
  private List<Map<String, Object>> history;
  private Map<String, Method> methods;
  private boolean initialized = false;


  public HeightmapOperator(int width, int height, int margin) {
    pending = new LinkedList<Map<String, Object>>();
    history = new LinkedList<Map<String, Object>>();
    initHeightmapMethods();

    Map<String, Object> init = new HashMap<String, Object>(3);
    init.put("qty", 1);
    init.put("name", new String("initialize"));
    init.put("args", Arrays.asList( new String[]{
      String.format("%d", width),
      String.format("%d", height),
      String.format("%d", margin)
    } ));
    pending.add(init);
    step(); // perform and register the init operation
  }


  public HeightmapOperator(String filename)
    throws HeightmapUninitializedException 
  {
    pending = new LinkedList<Map<String, Object>>();
    history = new LinkedList<Map<String, Object>>();
    initHeightmapMethods();
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


  private void initHeightmapMethods() {
    Method[] ms = Heightmap.class.getMethods();
    methods = new HashMap(ms.length);
    for (Method m : ms) {
      // skip (overloaded) normalize(max, min)
      if (m.getName().equals("normalize") && m.getParameterTypes().length != 0)
        continue;
      methods.put(m.getName(), m);
    }
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


  // TODO: throw exceptions for qties <= 0
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
        
        String[] tokens = s.split("\\s*[,\t]\\s*");
        Map<String, Object> m = new HashMap<String, Object>(3);
        m.put("qty", Integer.parseInt(tokens[0]));
        m.put("name", tokens[1]);

        List args = new LinkedList();
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


  /**
    Save operation history as CSV recipe file.
    All operations performed since initialization are written
    down with their exact quantity, parameters and in the order of applying
    to the Heightmap.
  */
  public void save(String filename) {
    try {
      PrintStream out = new PrintStream(filename);
      for (Map<String, Object> op : history) {
        int qty = (Integer)op.get("qty");
        String name = (String)op.get("name");
        List args = (List)op.get("args");

        StringBuilder argTxt = new StringBuilder();
        Iterator<String> argIter = args.iterator();
        while (argIter.hasNext())
          argTxt.append(", " + argIter.next());

        out.printf("%d, %s%s\n", qty, name, argTxt.toString());
      }
      out.close();
    } catch (IOException e) {
      e.printStackTrace();
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

    try {
      Map<String, Object> op = pending.get(0);
      final int qty = (Integer)op.get("qty");
      final String name = (String)op.get("name");
      final List args = (List)op.get("args");

      // perform operation
      if (name.equals("initialize")) {
        if (initialized) return; // (!) -- don't do registerOperation

        initialize( new Integer((String)args.get(0)),
          new Integer((String)args.get(1)), new Integer((String)args.get(2)) );
          // constructors used, as 'args' contains parseable strings

        // register in history
        registerOperation(op);
      } else {
        try {
          Method meth = methods.get(name);
          if (meth == null) {
            System.err.printf("Skipping unknown Heightmap operation: %s\n",
              name);
          }

          Class[] argTypes = meth.getParameterTypes();

          // dbg
          System.out.printf("%s\n", name);
          for (Class c : argTypes)
            System.out.println(c.toString());
          // end dbg

          // ugly... but there are only 3 types to check here so it must
          // stay that way for some time
          // TODO: make this less ugly
          Object[] argObjs = new Object[args.size()];
          for (int i = 0; i < args.size(); i++) {
            if (argTypes[i].equals(int.class))
              argObjs[i] = new Integer((String)args.get(i));
            else if (argTypes[i].equals(float.class))
              argObjs[i] = new Float((String)args.get(i) + "f");
            else 
              argObjs[i] = new Boolean((String)args.get(i));
          }

          meth.invoke(hmap, argObjs);
        } /*catch (NoSuchMethodException e) {
          System.err.printf("Can't find argument constructor for %s\n",
            name);
        }*/ catch (InvocationTargetException e) {
          System.err.printf(
            "Can't convert argument for method %s\n", name);
        } /*catch (InstantiationException e) {
          System.err.printf(
            "Can't convert argument for method %s\n", name);
        }*/ catch (IllegalAccessException e) {
          // can't happen for constructors (only public used), may for methods
          e.printStackTrace();
        }

        // register in history
        registerOperation(op);
      }
      // 'registerOperation' isn't performed here (though it happens
      // in both cases) as it might not be wanted in case of
      // 'initialize' operation appearing in 'pending' when the hmap
      // is already initialized; that's because of the if(...)->return
      // marked with (!)
    } catch (IndexOutOfBoundsException e) {
      // this mustn't happen
      e.printStackTrace();
    }
  }


  private void registerOperation(Map<String, Object> op) {
    final int qty = (Integer)op.get("qty");
    final String name = (String)op.get("name");
    final List args = (List)op.get("args");

    if (qty <= 1)
      pending.remove(0);

    Map<String, Object> prevOp =
      history.isEmpty() ? null : history.get(history.size() - 1);
    if (prevOp != null &&
        name.equals(prevOp.get("name")) &&
        args.equals(prevOp.get("args"))) {
      // op is in history, with different qty
      prevOp.put( "qty", ((Integer)prevOp.get("qty")) + 1 );
        // qty is stored as Integer in the Map, so only cast is required
        // in contrast to the stuation with 'initialize' args above
    } else { // op not yet in history
      Map<String, Object> newOp = new HashMap<String, Object>(3);
      newOp.put("qty", 1);
      newOp.put("name", name);
      newOp.put("args", args);
      history.add(newOp);
    }
    // in both cases decrease the qty in pending
    op.put( "qty", ((Integer)op.get("qty")) - 1 );
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
