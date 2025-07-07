#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int N = 5; // Cantidad de nodos

vector<int> adj[N];
bool visited[N];

// ---------------------------
// BFS Conectividad y Rutas Cortas
// ---------------------------
void bfs_conectividad(int start) {
    fill(visited, visited + N, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

void bfs_rutas_cortas(int start) {
    vector<int> dist(N, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

}

// ---------------------------
// BFS para Reconstrucción de Ruta Más Corta
// ---------------------------
void bfs_ruta_mas_corta(int inicio, int fin) {
    vector<int> dist(N, -1);
    vector<int> padre(N, -1); // Para reconstrucción de camino
    queue<int> q;

    dist[inicio] = 0;
    q.push(inicio);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                padre[v] = u;
                q.push(v);

                if (v == fin) break; // Podemos detenernos si encontramos el destino
            }
        }
    }

    if (dist[fin] == -1) {
        cout << "No existe ruta desde " << inicio << " a " << fin << endl;
        return;
    }

    // Reconstrucción del camino
    vector<int> ruta;
    for (int v = fin; v != -1; v = padre[v]) {
        ruta.push_back(v);
    }
    reverse(ruta.begin(), ruta.end());

    cout << "Ruta más corta de " << inicio << " a " << fin << ": ";
    for (int nodo : ruta) {
        cout << nodo << " ";
    }
    cout << "\nLongitud de la ruta: " << dist[fin] << endl;
}


// ---------------------------
// DFS Recursivo
// ---------------------------
void dfs_recursivo(int u) {
    visited[u] = true;
    cout << u << " ";

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs_recursivo(v);
        }
    }
}

// ---------------------------
// DFS Iterativo con Pila
// ---------------------------
void dfs_iterativo(int start) {
    fill(visited, visited + N, false);
    stack<int> st;

    st.push(start);

    cout << "DFS Iterativo desde " << start << ": ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";

            // Agregar vecinos al stack en orden inverso para simular comportamiento recursivo
            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                if (!visited[*it]) {
                    st.push(*it);
                }
            }
        }
    }
    cout << endl;
}

// ---------------------------
// Algoritmo de Tarjan - SCC
// ---------------------------
int index_counter = 0;
int indices[N], lowlink[N];
bool onStack[N];
stack<int> st;
vector<vector<int>> sccs;

void tarjanSCC(int u) {
    indices[u] = lowlink[u] = index_counter++;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (indices[v] == -1) {
            tarjanSCC(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (onStack[v]) {
            lowlink[u] = min(lowlink[u], indices[v]);
        }
    }

    if (lowlink[u] == indices[u]) {
        vector<int> scc;
        int v;
        do {
            v = st.top();
            st.pop();
            onStack[v] = false;
            scc.push_back(v);
        } while (v != u);
        sccs.push_back(scc);
    }
}

void ejecutar_tarjan() {
    fill(indices, indices + N, -1);
    fill(lowlink, lowlink + N, -1);
    fill(onStack, onStack + N, false);
    sccs.clear();
    index_counter = 0;

    for (int i = 0; i < N; ++i) {
        if (indices[i] == -1) {
            tarjanSCC(i);
        }
    }

    cout << "\nComponentes Fuertemente Conexos (SCC):\n";
    for (const auto& scc : sccs) {
        for (int node : scc) {
            cout << node << " ";
        }
        cout << endl;
    }
}

// ---------------------------
// Main - Construcción y Pruebas
// ---------------------------
int main() {
    // Construimos la lista de adyacencia del grafo de la imagen
    adj[0] = {3};
    adj[1] = {2, 4};
    adj[2] = {0, 1, 3};
    adj[3] = {0, 1, 2 ,4};
    adj[4] = {2, 3};

    cout << "BFS para conectividad:\n";
    bfs_conectividad(1);

    cout << "\nBFS para rutas más cortas:\n";
    bfs_rutas_cortas(1);

    cout << "\nDFS Recursivo:\n";
    fill(visited, visited + N, false);
    dfs_recursivo(0);
    cout << endl;

    cout << "\nDFS Iterativo:\n";
    dfs_iterativo(0);

    int inicio = 1;
    int fin = 0;

    cout << "\nbfs RUTA\n";
    bfs_ruta_mas_corta(inicio, fin);

    ejecutar_tarjan();

    return 0;
}
