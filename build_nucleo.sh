#
#!/bin/bash
#

set -e

cd Src
~/GitHub/toddsharpe/UBuild/latest.sh Build --project Nucleo --verbose --compiler Stm32
cd ..
