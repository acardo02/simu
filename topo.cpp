#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& topoStack) {
    visited[u] = true;

    // Visitamos todos los vecinos de u
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, topoStack);
        }
    }

    // Cuando terminamos de visitar a todos sus vecinos, lo apilamos
    topoStack.push(u);
}

vector<int> topological(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> topoStack;

    // Podemos empezar desde cualquier nodo no visitado
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, topoStack);
        }
    }

    // Sacamos los nodos del stack para obtener el orden topológico
    vector<int> topoOrder;
    while (!topoStack.empty()) {
        topoOrder.push_back(topoStack.top());
        topoStack.pop();
    }

    return topoOrder;
}

bool topologicalSort(int n, vector<vector<int>>& adj, vector<int>& result) {
    vector<int> in_degree(n, 0);

    // Calcular in-degree (número de aristas que entran a cada nodo)
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }

    queue<int> q;

    // Agregar nodos con in-degree 0
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Si pudimos procesar todos los nodos, es un DAG
    return result.size() == n;
}

int main() {
    // Ejemplo 1: Grafo SÍ es DAG
   int n = 3;
    vector<vector<int>> adj(n);

    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {};

    vector<int> result;
    

    vector<int> topoOrder = topological(n, adj);

    cout << "Orden Topologico: ";
    for (int node : topoOrder) {
        cout << node << " ";
    }

    if (topologicalSort(n, adj, result)) {
        cout << "El grafo es un DAG. Orden Topológico:\n";
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "El grafo NO es un DAG, tiene ciclos.\n";
    }


    return 0;
}
