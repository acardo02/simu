#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int N = 100;
int dist[N];
bool visited[N];
int adj[N][N]; // Matriz de adyacencia
int n; // Nodos

void dijkstra_cuadratica(int start) {
    fill(dist, dist + n, INF);
    fill(visited, visited + n, false);
    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        if (dist[u] == INF) break; // Nodo inaccesible
        visited[u] = true;

        for (int v = 0; v < n; ++v)
            if (adj[u][v] != INF && dist[v] > dist[u] + adj[u][v])
                dist[v] = dist[u] + adj[u][v];
    }
}

void dijkstra_logaritmica(int start, int n, vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    dist.assign(n, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; // Ya procesado

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void dijkstra_ruta(int start, int n, vector<vector<pair<int, int>>>& adj, vector<int>& dist, vector<int>& parent) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Función para reconstruir ruta
vector<int> reconstruir_ruta(int destino, vector<int>& parent) {
    vector<int> ruta;
    for (int v = destino; v != -1; v = parent[v])
        ruta.push_back(v);
    reverse(ruta.begin(), ruta.end());
    return ruta;
}

