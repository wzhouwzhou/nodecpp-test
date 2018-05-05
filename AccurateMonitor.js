exports.AccurateMonitor = class AccurateMonitor {
  set() {
    return this.start = process.hrtime();
  }

  report() {
    var end, hrTime, µs;
    hrTime = process.hrtime(this.start);
    µs = false;
    end = hrTime[0] * 1000 + hrTime[1] / 1000000;
    if (end < 1) {
      µs = true;
      end = hrTime[0] * 1000000 + hrTime[1] / 1000;
    }
    end += µs ? 'µs' : 'ms';
    return this.string = end;
  }

  toString() {
    var ref;
    return (ref = this.string) != null ? ref : this.report();
  }

};
