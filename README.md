# TEB_Library
This is the official library of Tiny Electronig Blog. Is designed to unify the management of development boards and add new features, such as:
- partial support to OAuth 2.0 (https://developers.google.com/identity/protocols/oauth2) and Google Drive API (https://developers.google.com/drive/api/v3/reference);
- basic time management with timezone and DST;
- an alternative method to manage large arrays;

and more. It not support all features of a development board; for example, there are currently no methods to control the bluetooth of an ESP32. For the moment, only the ESP32 development board is compatible.

Not all functions include error checking and not all types of bugs are handled; the instructions and methods for managing errors are present only when debugging is active, in order to lighten the source code when debugging is disabled.

Almost all classes that depend on libraries specific to a particular development board are contained in the development_board folder, making it easier to support a new board.

The library was not written aiming at maximum efficiency but to try to offer a good compromise between stability, efficiency and ease of editing, in order to simplify any future code changes.

The "Documentation.zip" file contains non-exhaustive written documentation, however there are test functions in all classes which also serve as examples.

The TEB_Library.h file contains various #defines that you can customize to suit your needs. The values API key, client id and client secret can be obtained by following the first part of the Google guide https://developers.google.com/identity/protocols/oauth2/limited-input-device#prerequisites.

To use the library, the file "TEB_Library.h" must be imported into your project using the command: #include "TEB_Library.h"

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
