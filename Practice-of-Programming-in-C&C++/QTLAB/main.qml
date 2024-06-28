import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick3D.Helpers

Window {
    id: window
    width: 1080
    height: 720
    visible: true
    title: "3D View of Topographic Map"
    color: "#848895"

    // The root scene
    //! [rootnode]
    Node {
        id: mainScene
        //! [rootnode]
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
                    source: appDir + "/meshes/" + meshSourceCentre
                    // source: "file:///E:/C++/objFileWriter/meshes/simple_mesh.mesh"
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

            /*Node {
                id: movingControler
                x: 750
                y: 300
                z: 750
            }*/

            PerspectiveCamera {
                id: cameraPerspectiveMain
                x: 750
                y: 300
                z: 750
                //x: movingControler.x
                //y: movingControler.y
                //z: movingControler.z
                //lookAtNode: rotatingObject
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
            importScene: mainScene
            renderMode: View3D.Underlay

            environment: SceneEnvironment {
                clearColor: window.color
                backgroundMode: SceneEnvironment.Color
            }
        }

        WasdController {
            id: wasd_control
            controlledObject: cameraPerspectiveMain
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
