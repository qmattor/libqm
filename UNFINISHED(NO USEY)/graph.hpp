// Quincy Mattor
// Copyright 2022

#include "matrix.hpp"

#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace libqm {

template <class T>
class vertex {
 private:
  std::vector edges;

 public:
  // do whatever you want with this, I'm just adding meta graph data
  T* data;
  vertex() = default;
  void add_edge(size_t v_num);
  void remove_edge(size_t v_num);
};

template <class T>
void vertex<T>::add_edge(size_t v_num) {
  for (auto x : this->edges)
    if (x == v_num) return;
  this->edges.push_back(v_num);
}

template <class T>
void vertex<T>::remove_edge(size_t v_num) {
  for (size_t i = 0; i < this->edges; i++)
    if (this->edges.at(i) == v_num) {
      std::swap(this->edges.at(i), this->edges.back());
      this->edges.pop_back();
      return;
    }
}

template <class T>
class graph {
 private:
  matrix<u_int16_t> adj_mat;
  std::vector<vertex<T>> vertex_list;

 public:
  graph();
  ~graph();
  void add_vertex(T data);
  void add_edge(size_t f, size_t t);
  T get_data(size_t v_num);
};

template <class T>
graph<T>::graph() {}

template <class T>
graph<T>::~graph() {}

template <class T>
void graph<T>::add_vertex(T data) {}

template <class T>
void graph<T>::add_edge(size_t f, size_t t) {}

}  // namespace libqm

#endif  // GRAPH_HPP
