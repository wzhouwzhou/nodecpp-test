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
exports.ArrayUtil = ArrayUtil;
exports.arrays = ArrayUtil;
