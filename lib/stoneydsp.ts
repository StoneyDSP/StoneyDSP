/**
 * The 'StoneyDSP' C++ addon interface.
 */
interface StoneyDSP {
  /**
   * Returns a string, confirming the StoneyDSP addon is online.
   * @returns string
   */
  hello(): string;
  /**
   * Returns a number, confirming the StoneyDSP API version number.
   * @returns number
   */
  version(): number;
}
const platform = process.platform;
var buildDir = "/build/lib/";

if(platform === "win32")
  buildDir = "\\build\\bin\\Release\\";

const StoneyDSP: StoneyDSP = require(`..${buildDir}stoneydsp.node`);
export = StoneyDSP;
