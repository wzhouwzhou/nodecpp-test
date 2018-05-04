'use strict';
Object.defineProperty(exports, '__esModule', { value: true });

const R = './build/Release/';

Object.defineProperty(exports, 'mathp', { value: `${R}math` });
Object.defineProperty(exports, 'hellop', { value: `${R}hello` });
Object.defineProperty(exports, 'arraysp', { value: `${R}arrays` });

exports.math = require(exports.mathp);

exports.hello = require(exports.hellop);

const { ArrayUtil } = require(exports.arraysp);
const AU_default = ArrayUtil(!0);
Object.defineProperties(ArrayUtil, {
  'sample': {
    value: AU_default.sample.bind(this && this.constructor === ArrayUtil ? this : AU_default),
    enumerable: !0,
  },
  'shuffle': {
    value: AU_default.shuffle.bind(this && this.constructor === ArrayUtil ? this : AU_default),
    enumerable: !0,
  },
  'sumAll': {
    value: AU_default.sumAll.bind(this && this.constructor === ArrayUtil ? this : AU_default),
    enumerable: !0,
  },
  'dot': {
    value: AU_default.dot.bind(this && this.constructor === ArrayUtil ? this : AU_default),
    enumerable: !0,
  }
})

Object.defineProperty(exports, 'ArrayUtil', { value: ArrayUtil });
exports.arrays = ArrayUtil;
