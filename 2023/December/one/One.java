import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

public class One {
  static StreamTokenizer st;
  static int N;

  public static class Node {
    List<Node> from = new ArrayList<>();
    List<Node> to = new ArrayList<>();
    int[] canReach; // how many ways it can reach a number
    int id;
    public Node(int id, int n)
    {
      this.id = id;
      canReach = new int[n];
    }

    @Override
    public String toString() {
      return Integer.toString(id);
    }
  }

  public static void main(String[] args) throws Exception {
    // read input
    // BufferedReader br = new BufferedReader(new FileReader("one.in"));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    st = new StreamTokenizer(br);
    // PrintWriter pw = new PrintWriter(new File("one.out"));
    PrintWriter pw = new PrintWriter(System.out);
    N = nextInt();
    
    // solve
    boolean[][] arr = new boolean[N-1][N-1];

    for (int i = 0; i < N-1; i++)
    {
      int cur = nextInt();
      String s = String.format("%0"+ ((N - i - 1)) + "d", cur);
      for (int j = 0; j < s.length(); j++)
      {
        arr[i][j] = s.charAt(j) == '0';
      }
    }

    Node[] nodes = new Node[N];
    for (int i = 0; i < N; i++)
    {
      nodes[i] = new Node(i, N);
    }

    for (int j = 0; j < N-1; j++)
    {
      for (int i = 0; i < N-1-j; i++)
      {
        boolean addEdge = false;
        if (arr[i][j]) // even
        {
          addEdge = nodes[i].canReach[i+j+1] % 2 == 1;
        } else // odd;
        {
          addEdge = nodes[i].canReach[i+j+1] % 2 == 0;
        }

        if (!addEdge) continue;

        nodes[i].to.add(nodes[i+j+1]);
        nodes[i+j+1].from.add(nodes[i]);

        Queue<Node> q = new ArrayDeque<>();
        boolean[] visited = new boolean[N];
        List<Integer> after = new ArrayList<>();
        q.add(nodes[i+j+1]);
        visited[i+j+1] = true;
        while (!q.isEmpty())
        {
          Node n = q.poll();
          nodes[i].canReach[n.id]++;
          after.add(n.id);

          for (Node nb : n.to)
          {
            if (!visited[nb.id])
            {
              q.add(nb);
              visited[nb.id] = true;
            }
          }
        }

        q.add(nodes[i]);
        visited[i] = true;

        while (!q.isEmpty())
        {
          Node n = q.poll();
          
          if (n.id != i) {
            for (int a : after)
            {
              n.canReach[a]++;
            }
          }

          for (Node nb : n.from)
          {
            if (!visited[nb.id])
            {
              q.add(nb);
              visited[nb.id] = true;
            }
          }
        }
      }
    }

    int result = 0;
    for (int i = 0; i < N; i++)
    {
      result += nodes[i].to.size();
    }

    pw.println(result);

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