import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "../../.."

    ofApp {
        name: { return FileInfo.baseName(path) }

        files: [
            'src/GuiApp.cpp',
            'src/GuiApp.h',
            'src/Resources/segment.cpp',
            'src/Resources/segment.h',
            'src/Resources/shadermanager.cpp',
            'src/Resources/shadermanager.h',
            'src/Resources/travelling.cpp',
            'src/Resources/travelling.h',
            'src/Seqs/circle_dancing.cpp',
            'src/Seqs/circle_dancing.h',
            'src/Seqs/flocking.cpp',
            'src/Seqs/flocking.h',
            'src/Seqs/lighthair.cpp',
            'src/Seqs/lighthair.h',
            'src/Seqs/moire.cpp',
            'src/Seqs/moire.h',
            'src/audioinput.cpp',
            'src/audioinput.h',
            'src/button.cpp',
            'src/button.h',
            'src/effect_template.cpp',
            'src/effect_template.h',
            'src/effectpanel.cpp',
            'src/effectpanel.h',
            'src/layer.cpp',
            'src/layer.h',
            'src/main.cpp',
            'src/mainpanel.cpp',
            'src/mainpanel.h',
            'src/modulframerate.cpp',
            'src/modulframerate.h',
            'src/nanokontrol2.cpp',
            'src/nanokontrol2.h',
            'src/nanopanel.cpp',
            'src/nanopanel.h',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src/output.cpp',
            'src/output.h',
            'src/pushbutton.cpp',
            'src/pushbutton.h',
        ]

        of.addons: [
            'ofxFft',
            'ofxGLWarper',
            'ofxGui',
            'ofxMidi',
            'ofxOpenCv',
            'ofxOsc',
            'ofxXmlSettings',
            'ofxDatGui',
            'ofxBeat',
            'ofxPostGlitch',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
