import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

public class Milkorder {
  static StreamTokenizer st;
  static int N;
  static int M;
  static Node[] nodes;
  static List<List<Integer>> edges = new ArrayList<>();

  static class Node {
    int parentCnt = 0;
    int id;
    boolean visited = false;
    List<Node> from = new ArrayList<>();
    List<Node> to = new ArrayList<>();

    public Node(int id) {
      this.id = id;
    }

    @Override
    public String toString() {
      return Integer.toString(id);
    }
  }

  static class Comp implements Comparator<Node> {
    @Override
    public int compare(Node x, Node y) {
      return x.id - y.id;
    }
  }

  public static void main(String[] args) throws Exception {
    // read input
    BufferedReader br = new BufferedReader(new FileReader("milkorder.in"));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    st = new StreamTokenizer(br);
    PrintWriter pw = new PrintWriter(new File("milkorder.out"));
    // PrintWriter pw = new PrintWriter(System.out);
    N = nextInt();
    M = nextInt();
    
    // solve

    nodes = new Node[N];
    for (int i = 0; i < N; i++) {
      nodes[i] = new Node(i);
    }


    for (int i = 0; i < M; i++) {
      int k = nextInt();
      List<Integer> curList = new ArrayList<>();
      for (int j = 0; j < k; j++) {
        curList.add(nextInt()-1);
      }

      edges.add(curList);
    }

    // binary search
    int low = 0;
    int high = M-1;
    
    while (low < high) { // notice we do not compare element at mid with our target
      int mid = low + (high - low + 1) / 2;
      List<Integer> result = check(mid);
      if (result.size() == N)
        low = mid;
      else
        high = mid - 1;
    }

    List<Integer> result2 = check(low);
    for (int i = 0; i < N-1; i++) {
      pw.print(result2.get(i)+1+" ");
    }

    pw.println(result2.get(N-1)+1);

    br.close();
    pw.close();
  }

  private static List<Integer> check(int x) {
    for (int i = 0; i <= x; i++) {
      for (int j = 0; j < edges.get(i).size()-1; j++) {
        nodes[edges.get(i).get(j)].to.add(nodes[edges.get(i).get(j+1)]);
        nodes[edges.get(i).get(j+1)].from.add(nodes[edges.get(i).get(j)]);
        nodes[edges.get(i).get(j+1)].parentCnt++;
      }
    }

    PriorityQueue<Node> queue = new PriorityQueue<Node>(new Comp());
    for (int i = 0; i < N; i++) {
      nodes[i].parentCnt = nodes[i].from.size();
      if (nodes[i].parentCnt == 0) {
        queue.add(nodes[i]);
        nodes[i].visited = true;
      }
    }
    List<Integer> result = new ArrayList<>();
    while (!queue.isEmpty()) {
      Node cur = queue.poll();
      result.add(cur.id);

      for (Node n : cur.to) {
        n.parentCnt--;
        if (n.parentCnt == 0) {
          queue.add(n);
          n.visited = true;
        }
      }
    }

    // reset
    for (int i = 0; i < N; i++) {
      nodes[i].to = new ArrayList<>();
      nodes[i].from = new ArrayList<>();
      nodes[i].parentCnt = 0;
      nodes[i].visited = false;
    }

    return result;
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