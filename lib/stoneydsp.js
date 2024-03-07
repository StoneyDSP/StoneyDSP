const platform = process.platform;
var buildDir = "/build/lib/";

if(platform === "win32")
  buildDir = "\\build\\bin\\Release\\";

const StoneyDSP = require(`..${buildDir}stoneydsp.node`);
module.exports = StoneyDSP;
