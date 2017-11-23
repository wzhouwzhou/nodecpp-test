'use strict';
Object.defineProperty(exports, '__esModule', { value: true });

const R = './build/Release/';

Object.defineProperty(exports, 'mathp', { value: `${R}math` });
Object.defineProperty(exports, 'hellop', { value: `${R}hello` });
Object.defineProperty(exports, 'arraysp', { value: `${R}arrays` });

delete require.cache[require.resolve(exports.mathp)];
exports.math = require(exports.mathp);

delete require.cache[require.resolve(exports.hellop)];
exports.hello = require(exports.hellop);

delete require.cache[require.resolve(exports.arraysp)];
const { ArrayUtil } = require(exports.arraysp);
const AU_default = ArrayUtil(!0);
Object.defineProperty(ArrayUtil, 'sample', {
  value: AU_default.sample.bind(this && this.constructor === ArrayUtil ? this : AU_default),
  enumerable: !0,
});
Object.defineProperty(ArrayUtil, 'shuffle', {
  value: AU_default.shuffle.bind(this && this.constructor === ArrayUtil ? this : AU_default),
  enumerable: !0,
});
Object.defineProperty(exports, 'ArrayUtil', { value: ArrayUtil });
exports.arrays = ArrayUtil;
