#
#!/bin/bash
#

set -e

cd Src
~/GitHub/toddsharpe/UBuild/latest.sh Build --project ${1:-All} --verbose --compiler ${2:-All}
cd ..
