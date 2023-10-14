import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

public class Dirtraverse {
  static class Node {
    ArrayList<Node> children = new ArrayList<>();
    boolean isFile;
    int val;
    int leafNum = 0;

    @Override
    public String toString() {
      return "" + leafNum;
    }
  };

  static StreamTokenizer st;
  static int N;
  static Node[] nodes;
  static int totLeaf = 0;
  static long result = Integer.MAX_VALUE;

  public static void main(String[] args) throws Exception {
    // read input
    BufferedReader br = new BufferedReader(new FileReader("dirtraverse.in"));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    st = new StreamTokenizer(br);
    PrintWriter pw = new PrintWriter(new File("dirtraverse.out"));
    // PrintWriter pw = new PrintWriter(System.out);
    N = nextInt();

    
    nodes = new Node[N];
    // solve
    for (int i = 0; i < N; i++) {
      nodes[i] = new Node();
    }

    // init nodes
    for (int i = 0; i < N; i++) {
      int val = nextString().length()+1;
      nodes[i].val = val;
      int num = nextInt();

      nodes[i].isFile = num==0;
      if (num == 0) {
        totLeaf++;
      }

      for (int j = 0; j < num; j++) {
        int cur = nextInt()-1;
        nodes[i].children.add(nodes[cur]);
      }
    }

    
    if (N == 1) {
      pw.println(nodes[0].val-1);
      br.close();
      pw.close();
      return;
    }

    // find leafNum and make init sum
    long[] dfs = dfs1(nodes[0]);

    // starting is dfs[1]
    // get result
    dfs2(nodes[0], dfs[1]);

    pw.println(result - totLeaf);

    br.close();
    pw.close();
  }

  private static long[] dfs1(Node cur) {
    if (cur.isFile) {
      return new long[]{1, 0};
    }

    int sum = 0;
    long sum2 = 0;
    for (Node n : cur.children) {
      long[] dfs = dfs1(n);
      sum += dfs[0];
      sum2 += dfs[1] + ((long)n.val * (n.leafNum == 0 ? 1 : n.leafNum));
    }

    cur.leafNum = sum;
    return new long[]{sum, sum2};
  }

  private static void dfs2(Node cur, long curSum) {
    result = Math.min(result, curSum);
    for (Node n : cur.children) {
      if (n.isFile) continue;

      long newSum = curSum - ((long) n.leafNum * n.val) + ((long) (totLeaf-n.leafNum) * 3);
      dfs2(n, newSum);
    }
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