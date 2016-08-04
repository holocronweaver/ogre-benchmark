import copy
import os

#TODO: Support Windows.

#TODO: Make user specify?
ogreInstall = '/home/jesse/lib/built/ogre2'
ogreBuild = '/home/jesse/lib/build/ogre2'
ogreSamplesSrc = '/home/jesse/lib/graphics/ogre/Samples/2.0'

flags = ['-std=c++14', '-O2', '-g']
cppdefines = []
libs = [
    'OgreSamplesCommon_d',
    'OgreOverlay_d',
    'OgreMain_d',
    'OgreHlmsPbs_d',
    'OgreHlmsUnlit_d',
    'boost_system',
    'SDL2'
]
libpaths = [
    ogreInstall + '/lib/OGRE',
    ogreBuild + '/lib'
]
includes = [
    '.',
    #FIXME: Grr....OGRE doesn't search system paths.
    '/usr/local/include/SDL2',
    ogreInstall + '/include/OGRE',
    ogreInstall + '/include/OGRE/Overlay',
    # ogreInstall + '/include/OGRE/RenderSystems/GL3Plus/include',
    ogreSamplesSrc + '/Common/include'
]

#TODO: Remove once scons bug fixed.
linkflags = copy.deepcopy(flags)
linkflags += ['-I'+path for path in includes]
linkflags += ['-D'+define for define in cppdefines]

env = Environment(
    CPPDEFINES=cppdefines,
    LIBPATH=libpaths,
    CPPPATH=includes,
    LIBS=libs,
    CXXFLAGS=flags,
    LINKFLAGS=linkflags,
    ENV = {'PATH' : os.environ['PATH']},
)
# Linux.
env['ENV']['TERM'] = os.environ['TERM']

# Rpath to find libraries relative to current directory.
env.Append(LINKFLAGS = Split('-z origin'))
env.Append(RPATH = ogreInstall + '/lib')

pyramids_source = Glob('OgrePyramids*.cpp') + Glob('OgrePyramids*.h')

env.Program('pyramids', pyramids_source)
