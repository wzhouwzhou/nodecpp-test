'use strict';
Object.defineProperty(exports, '__esModule', { value: true });
const { AccurateMonitor } = require('./AccurateMonitor');
const M = new AccurateMonitor;
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
  },
  'dotExp': {
    value: (...args) => {
      M.set();
      const v = AU_default.nativedotexp.bind(this && this.constructor === ArrayUtil ? this : AU_default)(...args);
      console.log(M.report());
      return v;
    },
    enumerable: !0,
  },
  'wrappedDotExp': {
    value: (...args) => {
      M.set();
      const v = AU_default.dotexp.bind(this && this.constructor === ArrayUtil ? this : AU_default)(...args);
      console.log(M.report());
      return v;
    },
    enumerable: !0,
  },
  'generate_diag_mat': {
    value: (x = 2, n = 100) => [...new Array(n)].map(() => ([...new Array(n).fill(0)])).map((row, i) => (row[i] = x, row)),
    enumerable: !0,
  },
});

Object.defineProperty(exports, 'ArrayUtil', { value: ArrayUtil });
exports.arrays = ArrayUtil;
