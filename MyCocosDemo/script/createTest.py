# Filename: createTest.py

import sys
import time
import os

header_template_file = './test_template_header'
source_template_file = './test_template_source'

out_path = '../Classes/TestCase/'
# get param
if len(sys.argv) < 2:
    print "Please input class name."
    sys.exit(0)

className = sys.argv[1]

# get create date
createDate = time.strftime('%m/%d/%y',time.localtime(time.time()))

# create Header File
headerTemplateFile = file(header_template_file,'r')
headerFile = out_path + className + '.h'

if os.path.exists(headerFile):
    print headerFile + ' has already exists!'
else:
    headerOutData = file(headerFile, 'w')

    for line in headerTemplateFile:
        outLine = line.replace('#CLASSNAME#', className).replace('#TIME#', createDate)
        headerOutData.write(outLine)
    headerOutData.close()

    print headerFile + ' has created!'

headerTemplateFile.close()


# create Source File
sourceTemplateFile = file(source_template_file,'r')
sourceFile = out_path + className + '.cpp'

if os.path.exists(sourceFile):
    print sourceFile + ' has already exists!'
else:
    sourceOutData = file(sourceFile, 'w')

    for line in sourceTemplateFile:
        outLine = line.replace('#CLASSNAME#', className).replace('#TIME#', createDate)
        sourceOutData.write(outLine)
    sourceOutData.close()

    print sourceFile + ' has created!'

sourceTemplateFile.close()


sys.exit(0)
