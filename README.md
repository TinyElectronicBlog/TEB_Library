# TEB_Library
This is the official library of Tiny Electronig Blog. It is designed to be able to control different devices with the same source code. Includes various features, such as:
- partial support to OAuth 2.0 (https://developers.google.com/identity/protocols/oauth2) and Google Drive API (https://developers.google.com/drive/api/v3/reference);
- basic time management with time zone and DST;
- an alternative method to manage large arrays;
- basic error detection;

and more. It not support all features of a device; for example, there are currently no methods to control the bluetooth of an ESP32. For the moment, only the ESP32 is supported.

Not all functions include error detection and not all types of bugs are handled.

All external dependencies are contained in the files "TEB_DeviceInterfaces", making it easier to support a new device.

The file TEB_LibrarySettings.h contains several #definitions that can be customized to suit own needs; the values API key, client id and client secret can be obtained by following the first part of the Google guide https://developers.google.com/identity/protocols/oauth2/limited-input-device#prerequisites or the video tutorial https://youtu.be/n38o2WiOiX8?t=623.

To use the library, the file "TEB_Library.h" must be imported into a project using the instruction: #include "TEB_Library.h"

The library is written to be compatible with C and C++ languages and various compilers; to know how to change language and compiler see the file "TEB_Library.h".

Google™, Android™, Google Drive™ and their respective logos are trademarks of Google Inc. registered in the United States and other countries.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
