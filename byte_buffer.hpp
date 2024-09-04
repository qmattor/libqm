/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_buffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:17:01 by qmattor           #+#    #+#             */
/*   Updated: 2024/09/04 12:49:44 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.hpp"

namespace libqm {
template <int BSIZE>
class bytebuffer {
 private:
  uint8_t mask = 0x1;
  uint8_t width;
  uint32_t length;
  uint32_t size;
  uint8_t *buffer;

 public:
  bytebuffer(bytebuffer &&other) {
    mask = other.mask;
    width = other.width;
    length = other.lenght;
    size = other.size;
    buffer = new uint8_t[1];
    std::swap(buffer, other.buffer);
  }

  bytebuffer(const bytebuffer &other) {
    mask = other.mask;
    width = other.width;
    length = other.lenght;
    size = other.size;
    for (int x = 0; x < length; x++) {
      buffer[x] = other.buffer[x];
    }
  }

  bytebuffer(size_t size)
      : width(8 / BSIZE),
        length(size / width + 1),
        size(size),
        buffer(new uint8_t[length]) {
    memset(buffer, 0, length);
    switch (BSIZE) {
      case 1:
        mask = 0x1;
        break;
      case 2:
        mask = 0x3;
        break;
      case 4:
        mask = 0xF;
        break;
      default:
        QM_exception(std::runtime_error("invalid size"));
    }
  }

  ~bytebuffer() { delete[] buffer; }

  uint8_t get(size_t idx) {
    log("getting idx %d\n", idx);
    return (buffer[idx / width] & (mask << ((idx % width) * BSIZE))) >>
           ((idx % width) * BSIZE);
  }
  void set(uint8_t data, size_t idx) {
    log("setting idx %i with value %i\n", idx, data);
    buffer[idx / width] &= ~(mask << ((idx % width) * BSIZE));
    buffer[idx / width] |= (mask & data) << ((idx % width) * BSIZE);
  }
  void clear() { memset(buffer, 0, length); }
};
};  // namespace libqm
