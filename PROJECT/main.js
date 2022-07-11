import * as THREE from './js/three.module.js'
import { OrbitControls } from './js/OrbitControls.js'
import { TransformControls } from './js/TransformControls.js'
import { GUI } from './js/dat.gui.module.js'
import Stats from './js/stats.module.js'
import { TeapotGeometry } from './js/TeapotGeometry.js';
import { GLTFLoader } from './js/GLTFLoader.js';



//global variables
let camera, scene, renderer
let floor, geometry, material, mesh, floorMesh, light, axes
let gui
let stats
let loader_3d = new GLTFLoader()
let root, light_model
let flag = 1
let textureLoader = new THREE.TextureLoader()

//control 
let obControls, afControls;

//GUI settings
let settings = {
    common: {
        showaxes: true,
        background: 'rgb(13,234,141)',
        Dfloor : true
    },
    geometry: {
        scale: 1,
        shape: 'cube',
        material: 'basic',
        wireframe: false,
        color: 0xF90C53,
    },
    model_view: {
        fov: 150,
        far: 1500,
        posX: 0,
        posY: 100,
        posZ: 800,
    },
    light: {
        type: 'point',
        enable: true,
        shadow: true,
        intensity: 1,
        color: 0xffffff,
        posY: 2,
        posZ: 0,
        posX: 0,
    },
    affine: {
        mode: 'none',
    },
    camera: {
        fov: 75,
        near: 0.1,
        far: 100,
        posX: 1,
        posY: 2,
        posZ: 4,
        lookX: 0,
        lookY: 0,
        lookZ: 0,
    },
    animation: {
        play: false,
        type: 'go up and down',
    }
}


function init() {

// Init scene
scene = new THREE.Scene();
scene.background = new THREE.Color( settings.common.background );

// Init stats
stats = Stats()
document.body.appendChild(stats.dom)


// Init camera (PerspectiveCamera)
camera = new THREE.PerspectiveCamera(settings.camera.fov, window.innerWidth / window.innerHeight, settings.camera.near, settings.camera.far);
camera.position.set(settings.camera.posX, settings.camera.posY, settings.camera.posZ)
camera.lookAt(settings.camera.lookX, settings.camera.lookY, settings.camera.lookZ)

// Init renderer
renderer = new THREE.WebGLRenderer({ antialias: true })
renderer.setSize(window.innerWidth, window.innerHeight)
renderer.setPixelRatio(window.devicePixelRatio)
renderer.shadowMap.enabled = true
renderer.shadowMap.type = THREE.PCFSoftShadowMap
document.body.appendChild(renderer.domElement)

// Init axes
axes = new THREE.AxesHelper(150)
scene.add(axes)

// Init floor
geometry = new THREE.PlaneBufferGeometry(10, 10, 10, 10)
let floorMat = new THREE.MeshPhongMaterial({ color: 0x222222, side: THREE.DoubleSide })
floor = new THREE.Mesh(geometry, floorMat)

// floor mesh
floorMesh = new THREE.Mesh(geometry, floorMat)
floorMesh.rotation.x = -Math.PI / 2
floorMesh.position.y = -.5
floorMesh.receiveShadow = true
scene.add(floorMesh)

//Init object
geometry = new THREE.BoxBufferGeometry(1, 1, 1)
material = new THREE.MeshBasicMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
mesh = new THREE.Mesh(geometry, material)
mesh.position.set(0, 0.5, 0)
mesh.castShadow = true
mesh.receiveShadow = false
scene.add(mesh)

//Init light
light = new THREE.PointLight(settings.light.color, 2, 100)
light.position.set(settings.light.posX, settings.light.posY, settings.light.posZ)
light.castShadow = true

//Init shadow
light.shadow.mapSize.width = 1024
light.shadow.mapSize.height = 1024
light.shadow.camera.near = 0.5
light.shadow.camera.far = 50

// add light to scene
scene.add(light)


// orbit controls
obControls = new OrbitControls(camera, renderer.domElement)
obControls.enableDamping = true
obControls.dampingFactor = 0.25
obControls.enableZoom = true
obControls.minDistance = 0.5
obControls.maxDistance = 1000
obControls.minPolarAngle = 0
obControls.maxPolarAngle = Math.PI / 2

// affine controls
afControls = new TransformControls(camera, renderer.domElement)
afControls.addEventListener('change', () => {
    renderer.render(scene, camera)
})
afControls.addEventListener('dragging-changed', (event) => {
    if (event.value) {
        obControls.enabled = false
    } else {
        obControls.enabled = true
    }
})
scene.add(afControls)
}

function loadmodel() {
    loader_3d.load(
    //model here
    '3d_model/scene.gltf',
    (gltf) => {
        root = gltf.scene;
        scene.add(root);
    }
    
);
    scene.remove(mesh)
    scene.remove(floorMesh)    
    scene.remove(axes)

    camera.far = settings.model_view.far
    camera.updateProjectionMatrix()
    camera.position.set(settings.model_view.posX,settings.model_view.posY,settings.model_view.posZ)
    camera.lookAt(0,0,0)

    light_model = new THREE.AmbientLight(0xffffff)
    light_model.intensity = 2
    scene.add(light_model)
    scene.remove(light)
}

function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight
    camera.updateProjectionMatrix()
    renderer.setSize(window.innerWidth, window.innerHeight)
    renderer.render(scene, camera)
}

function animate() {
    requestAnimationFrame(animate)

    if (settings.animation.play) {
        switch (settings.animation.type) {
            case 'go up and down':
                mesh.position.y = Math.sin(performance.now() * 0.001) * 0.75
                break
            case 'go left and right':
                mesh.position.x = Math.sin(performance.now() * 0.001) * 0.75
                break
            case 'rotate':
                mesh.rotation.x = performance.now() * 0.001
                mesh.rotation.y = performance.now() * 0.001
                break
            case 'go around':
                mesh.position.x = Math.sin(performance.now() * 0.001) * 0.75
                mesh.position.z = Math.cos(performance.now() * 0.001) * 0.75
                break
            case 'go around and rotate':
                mesh.rotation.x = performance.now() * 0.001
                mesh.rotation.y = performance.now() * 0.001
                mesh.position.x = Math.sin(performance.now() * 0.001) * 0.75
                mesh.position.z = Math.cos(performance.now() * 0.001) * 0.75
                break
            default:
                break
        }
    }

    stats.update()
    renderer.render(scene, camera)
}

function initGUI() {
    // gui  
    gui = new GUI()

    // common
    let h = gui.addFolder('common')

    h.addColor(settings.common, 'background').onChange(() => {
        scene.background = new THREE.Color(settings.common.background)
    })

    h.add(settings.common, 'showaxes').onChange(() => {
        if (settings.common.showaxes) {
            scene.add(axes)
        } else {
            scene.remove(axes)
        }
    })

    // geometry
    let g = gui.addFolder('geometry')
    g.add(settings.geometry, 'scale', 0.1, 10).onChange(() => {
        if (mesh) {
            mesh.scale.set(settings.geometry.scale, settings.geometry.scale, settings.geometry.scale)
        }
    })

    g.add(settings.geometry, 'shape', ['cube', 'sphere', 'cone', 'cylinder', 'dodecahedron', 'tetrahedron', 'torus', 'torusknot', 'teapot']).onChange(() => {
        if (settings.geometry.shape === 'cube') {
            geometry = new THREE.BoxBufferGeometry(1, 1, 1)
        } else if (settings.geometry.shape === 'sphere') {
            geometry = new THREE.SphereBufferGeometry(1, 32, 32)
        } else if (settings.geometry.shape === 'cone') {
            geometry = new THREE.ConeBufferGeometry(1, 2, 32)
        } else if (settings.geometry.shape === 'cylinder') {
            geometry = new THREE.CylinderBufferGeometry(1, 1, 1, 32)
        } else if (settings.geometry.shape === 'dodecahedron') {
            geometry = new THREE.DodecahedronBufferGeometry(1, 0)
        } else if (settings.geometry.shape === 'tetrahedron') {
            geometry = new THREE.TetrahedronBufferGeometry(1, 0)
        } else if (settings.geometry.shape === 'torus') {
            geometry = new THREE.TorusBufferGeometry(1, 0.3, 32, 32)
        } else if (settings.geometry.shape === 'torusknot') {
            geometry = new THREE.TorusKnotBufferGeometry(1, 0.1, 32, 32)
        } else if (settings.geometry.shape === 'teapot') {
            geometry = new TeapotGeometry(0.5)
        }
        mesh.geometry = geometry
        mesh.position.set(0, 0.5, 0)
    })

    g.add(settings.geometry, 'material', ['basic', 'lambert', 'phong', 'wireframe', 'crate texture','brick texture']).onChange(() => {
        if (settings.geometry.material === 'basic') {
            material = new THREE.MeshBasicMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'lambert') {
            material = new THREE.MeshLambertMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'phong') {
            material = new THREE.MeshPhongMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'crate texture') {
            material = new THREE.MeshBasicMaterial({ 
                map: textureLoader.load("./textures/crate.gif"),
                side:  THREE.DoubleSide 
            })         
        } else if (settings.geometry.material === 'wireframe') {
            material = new THREE.MeshBasicMaterial({ color: settings.geometry.color, wireframe: true, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'brick texture') {
            material = new THREE.MeshBasicMaterial({ 
                map: textureLoader.load("./textures/brick_diffuse.jpg"),
                side:  THREE.DoubleSide 
            })         
        }
        mesh.material = material
    })

    g.addColor(settings.geometry, 'color').onChange(() => {
        if (settings.geometry.material === 'basic') {
            material = new THREE.MeshBasicMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'lambert') {
            material = new THREE.MeshLambertMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        } else if (settings.geometry.material === 'phong') {
            material = new THREE.MeshPhongMaterial({ color: settings.geometry.color, side: THREE.DoubleSide })
        }
        mesh.material = material
    })

    // affine
    let f = gui.addFolder('affine transformation')
    f.add(settings.affine, 'mode', ['none', 'translate', 'rotate', 'scale']).onChange(() => {
        if (settings.affine.mode === 'none') {
            afControls.detach()
        } else {
            afControls.setMode(settings.affine.mode)
            afControls.attach(mesh)
        }
        mesh.position.set(0, 0.5, 0)
    })

    // light
    let l = gui.addFolder('light and shadow')
    l.add(settings.light, 'type', ['point', 'spot', 'directional']).onChange(() => {
        scene.remove(light)
        if (settings.light.type === 'point') {
            light = new THREE.PointLight(settings.light.color, 2, 100)
        } else if (settings.light.type === 'spot') {
            light = new THREE.SpotLight(settings.light.color, 2, 100)
        } else if (settings.light.type === 'directional') {
            light = new THREE.DirectionalLight(settings.light.color, 2)
        }
        light.position.set(settings.light.posX, settings.light.posY, settings.light.posZ)
        light.castShadow = settings.light.shadow
        scene.add(light)
    })

    l.add(settings.light, 'intensity', 0, 10).onChange(() => {
        light.intensity = settings.light.intensity
    })

    l.add(settings.light, 'shadow', false).onChange(() => {
        light.castShadow = settings.light.shadow
    })

    l.addColor(settings.light, 'color').onChange(() => {
        light.color = new THREE.Color(settings.light.color)
    })

    l.add(settings.light, 'posX', -10, 10).onChange(() => {
        light.position.set(settings.light.posX, settings.light.posY, settings.light.posZ)
    })

    l.add(settings.light, 'posY', -10, 10).onChange(() => {
        light.position.set(settings.light.posX, settings.light.posY, settings.light.posZ)
    })

    l.add(settings.light, 'posZ', -10, 10).onChange(() => {
        light.position.set(settings.light.posX, settings.light.posY, settings.light.posZ)
    })

    // camera
    let c = gui.addFolder('camera')
    c.add(settings.camera, 'fov', 1, 180).onChange(() => {
        camera.fov = settings.camera.fov
        camera.updateProjectionMatrix()
    })

    c.add(settings.camera, 'near', 0.1, 10).onChange(() => {
        camera.near = settings.camera.near
        camera.updateProjectionMatrix()
    })

    c.add(settings.camera, 'far', 0.1, 1000).onChange(() => {
        camera.far = settings.camera.far
        camera.updateProjectionMatrix()
    })

    c.add(settings.camera, 'posX', -10, 10).onChange(() => {
        camera.position.set(settings.camera.posX, settings.camera.posY, settings.camera.posZ)
    })

    c.add(settings.camera, 'posY', -10, 10).onChange(() => {
        camera.position.set(settings.camera.posX, settings.camera.posY, settings.camera.posZ)
    })

    c.add(settings.camera, 'posZ', -10, 10).onChange(() => {
        camera.position.set(settings.camera.posX, settings.camera.posY, settings.camera.posZ)
    })

    c.add(settings.camera, 'lookX', -10, 10).onChange(() => {
        camera.lookAt(settings.camera.lookX, settings.camera.lookY, settings.camera.lookZ)
    })

    c.add(settings.camera, 'lookY', -10, 10).onChange(() => {
        camera.lookAt(settings.camera.lookX, settings.camera.lookY, settings.camera.lookZ)
    })

    c.add(settings.camera, 'lookZ', -10, 10).onChange(() => {
        camera.lookAt(settings.camera.lookX, settings.camera.lookY, settings.camera.lookZ)
    })

    // animation
    let a = gui.addFolder('animation')
    a.add(settings.animation, 'play', false)

    a.add(settings.animation, 'type', ['go up and down', 'go left and right', 'rotate', 'go around', 'go around and rotate'])

    
    let m = { add:function(){ 
        if (flag == 1){
            loadmodel()
        }
        flag = 0
    }};

    let rm = { add:function(){ 
        flag = 1
        scene.remove(root)
        scene.remove(light_model)

    }};

    gui.add(m,'add').name('Load');
    gui.add(rm,'add').name('Remove 3D model');

    let d = { add:function(){  
        camera.position.set(settings.camera.posX, settings.camera.posY, settings.camera.posZ)
        camera.lookAt(settings.camera.lookX, settings.camera.lookY, settings.camera.lookZ)
        scene.add(mesh)
        scene.add(floorMesh)  
        scene.add(light)  
        scene.add(axes)

    }};
    gui.add(d,'add').name('Display geometry');

    
    gui.add(settings.common, 'Dfloor').onChange(() => {
        if (settings.common.Dfloor) {
            scene.add(floorMesh)
        } else {
            scene.remove(floorMesh)
        }
    })

}



init()
initGUI()
animate()