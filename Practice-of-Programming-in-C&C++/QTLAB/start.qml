import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick3D.Helpers

Item {
    id: window
    width: 1080
    height: 720
    visible: true
    //title: "Main Menu"
    //color: "#C0C0C0"


    // The root scene
    //! [rootnode]
    Node {
        id: standAloneScene
        //! [rootnode]

        Node {
            id: mainObject
            x: 750
            y: 0
            z: 750

            Node {
                id: rotatingObject
                x: 750 + 200 * parent.forward.x
                y: 0
                z: 750 + 200 * parent.forward.z
            }

            PropertyAnimation on eulerRotation.y {
                loops: Animation.Infinite
                duration: 20000
                to: 0
                from: -360
            }

        }

        DirectionalLight {
            ambientColor: Qt.rgba(0.5, 0.5, 0.5, 1.0)
            brightness: 1.0
            eulerRotation.x: -25
        }

        Node {
            id: test_mesh

            // Resources
            PrincipledMaterial {
                id: defaultMaterial_material
                objectName: "DefaultMaterial"
                baseColor: "#ff999999"
                indexOfRefraction: 1
            }

            // Nodes:
            Node {
                id: test_obj
                objectName: "test.obj"
                Model {
                    id: defaultobject
                    objectName: "defaultobject"
                    //source: appDir + "/menumesh.mesh"
                    source: "file:menumesh.mesh"
                    //source: "file:///D:/defaultobject_mesh.mesh"
                    //source: "C:/Users/Lucha/Desktop/QtRelease/mingw_64/bin/meshes/defaultobject_mesh.mesh"
                    //source: appDir + "/meshes/defaultobject_mesh.mesh"
                    materials: [
                        defaultMaterial_material
                    ]
                }
            }

        }

        //! [cameras start]
        // The predefined cameras. They have to be part of the scene, i.e. inside the root node.
        // Animated perspective camera
        Node {
            PerspectiveCamera {
                id: cameraPerspectiveMain
                x: 750
                y: 300
                z: 750
                lookAtNode: rotatingObject
            }
/*
            PropertyAnimation on eulerRotation.y {
                loops: Animation.Infinite
                duration: 50000
                to: 0
                from: -360
            }
*/
        }

    }
    //! [cameras end]

    Rectangle {
        id: mainRect
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "transparent"
        border.color: "black"

        View3D {
            id: mainView
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom;
            camera: cameraPerspectiveMain
            importScene: standAloneScene
            renderMode: View3D.Underlay

            environment: SceneEnvironment {
                clearColor: "#C0C0C0"
                backgroundMode: SceneEnvironment.Color
            }
        }

        WasdController {
            id: wasd_control
            controlledObject: mainView.camera
        }



        MouseArea {
            visible: !wasd_control.activeFocus
            anchors.fill: parent
            onClicked: {
                wasd_control.forceActiveFocus()
            }
        }

    }

}
