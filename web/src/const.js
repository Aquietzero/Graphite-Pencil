/*
 * Defines some constants that maybe useful in this application.
 */

var Const = {

  ZERO: 0.00001,

}

var Utils = {

  sum: function() {
    sum = 0;
    for (var i = 0; i < arguments.length; ++i)
      sum += arguments[i];
    return sum;
  },

}
