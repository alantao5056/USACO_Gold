import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

class Snow {
  int val;
  Snow next = null;
  int nextDist = 1;
  Snow prev = null;
  int prevDist = 1;

  Snow(int val) {
    this.val = val;
  }

  @Override
  public String toString() {
    return Integer.toString(val);
  }
};

class Boot {
  int depth;
  int step;
  boolean result;
  int idx;

  Boot(int depth, int step, int idx) {
    this.depth = depth;
    this.step = step;
    this.idx = idx;
  }

  @Override
  public String toString() {
    return depth + " " + step;
  }
};

class Comp implements Comparator<Snow> {
  public int compare(Snow c1, Snow c2) {
    return c1.val > c2.val ? 1 : -1;
  }
}

public class Snowboots {
  static StreamTokenizer st;
  static int N;
  static int B;

  public static void main(String[] args) throws Exception {
    // read input
    BufferedReader br = new BufferedReader(new FileReader("snowboots.in"));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    st = new StreamTokenizer(br);
    PrintWriter pw = new PrintWriter(new File("snowboots.out"));
    // PrintWriter pw = new PrintWriter(System.out);
    N = nextInt();
    B = nextInt();

    if (N == 1) {
      for (int i = 0; i < B; i++) {
        pw.println(1);
      }
      br.close();
      pw.close();
      return;
    }

    // solve
    Snow[] snow = new Snow[N];
    for (int i = 0; i < N; i++) {
      snow[i] = new Snow(nextInt());
    }

    snow[0].next = snow[1];
    snow[N-1].prev = snow[N-2];

    for (int i = 1; i < N-1; i++) {
      snow[i].prev = snow[i-1];
      snow[i].next = snow[i+1];
    }

    Arrays.sort(snow, new Comparator<Snow>() {
      public int compare(Snow s1, Snow s2) {
        if (s1.val < s2.val) {
          return 1;
        } else if (s1.val > s2.val) {
          return -1;
        }
        return 0;
      }
    });

    Boot[] boots = new Boot[B];
    for (int i = 0; i < B; i++) {
      boots[i] = new Boot(nextInt(), nextInt(), i);
    }

    Arrays.sort(boots, new Comparator<Boot>() {
      public int compare(Boot s1, Boot s2) {
        if (s1.depth < s2.depth) {
          return 1;
        } else if (s1.depth > s2.depth) {
          return -1;
        }
        return 0;
      }
    });

    int b = 0;
    int s = 0;
    int maxStep = 1;

    while (b < boots.length) {
      while (snow[s].val > boots[b].depth) {
        Snow next = snow[s].next;
        Snow prev = snow[s].prev;
        int totDist = snow[s].prevDist + snow[s].nextDist;
        next.prev = prev;
        next.prevDist = totDist;

        prev.next = next;
        prev.nextDist = totDist;

        maxStep = Math.max(maxStep, totDist);

        s++;
      }

      if (boots[b].step >= maxStep) {
        // true
        boots[b].result = true;
      } else {
        boots[b].result = false;
      }
      b++;
    }

    Arrays.sort(boots, new Comparator<Boot>() {
      public int compare(Boot s1, Boot s2) {
        return s1.idx > s2.idx ? 1 : -1;
      }
    });

    for (int i = 0; i < B; i++) {
      pw.println(boots[i].result ? 1 : 0);
    }

    br.close();
    pw.close();
  }

  private static int nextInt() throws Exception {
    st.nextToken();
    return (int) st.nval;
  }

  private static String nextString() throws Exception {
    st.nextToken();
    return st.sval;
  }
}