import glob
import os
import subprocess
import tempfile

rescompilerPath = 'build-desktop/bin/rescompiler.exe'
containerPath = 'data/build/game.dat'

excludeFiles = glob.glob('data/build/**/*', recursive=True) + glob.glob('data/sources/**/*', recursive=True)
dataFiles = [os.path.abspath(f) for f in glob.glob('data/**/*', recursive=True) if (not f in excludeFiles and not os.path.isdir(f))]
listFile = tempfile.NamedTemporaryFile('w+', delete=False)

print(f'Writing {len(dataFiles)} files to {listFile.name}')
listFile.write(os.linesep.join(dataFiles))
listFile.flush()
listFile.close()

resArgs = [
    os.path.abspath(rescompilerPath),
    listFile.name,
    os.path.abspath(containerPath)
]

returnCode = subprocess.call(resArgs)
print(f'Completed with code {returnCode}')