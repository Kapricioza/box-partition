let scene, camera, renderer, controls, allData = null;
let currentIdx = 0;
const group = new THREE.Group();


const clippingPlanes = [
    new THREE.Plane(new THREE.Vector3(-1, 0, 0), 10),
    new THREE.Plane(new THREE.Vector3(0, -1, 0), 10),
    new THREE.Plane(new THREE.Vector3(0, 0, -1), 10)
];

init();

function init() {
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0x111111);
    
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(10, 10, 10);

    renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.localClippingEnabled = true; // Włączenie przekrojów
    document.getElementById('canvas-container').appendChild(renderer.domElement);

    controls = new THREE.OrbitControls(camera, renderer.domElement);
    
    // Oświetlenie
    scene.add(new THREE.AmbientLight(0xffffff, 0.6));
    const light = new THREE.PointLight(0xffffff, 1);
    light.position.set(20, 20, 20);
    scene.add(light);

    scene.add(group);

    setupEventListeners();
    loadJSON();
    animate();
}

async function loadJSON() {
    try {
        const res = await fetch('./data/results.json');
        if (!res.ok) throw new Error("Brak pliku danych");
        allData = await res.json();
        
        // Aktualizacja suwaków pod nowe wymiary
        document.getElementById('clip-x').max = allData.m;
        document.getElementById('clip-y').max = allData.n;
        document.getElementById('clip-z').max = allData.k;
        
        renderCurrent();
    } catch (err) {
        document.getElementById('status').innerText = "Czekam na dane...";
    }
}

function renderCurrent() {
    if (!allData || allData.partitions.length === 0) return;
    group.clear();
    
    const partition = allData.partitions[currentIdx];
    document.getElementById('current-info').innerText = `${currentIdx + 1} / ${allData.total_partitions}`;

    partition.layout.forEach((block, i) => {
        const geo = new THREE.BoxGeometry(block.dx, block.dy, block.dz);
        const mat = new THREE.MeshPhongMaterial({
            color: new THREE.Color(`hsl(${(i * 55) % 360}, 70%, 60%)`),
            transparent: true,
            opacity: 0.7,
            clippingPlanes: clippingPlanes,
            side: THREE.DoubleSide
        });

        const mesh = new THREE.Mesh(geo, mat);
        // Centrowanie: Three.js ustawia środek boxa w (0,0,0)
        mesh.position.set(block.x + block.dx/2, block.y + block.dy/2, block.z + block.dz/2);

        // Krawędzie dla kontrastu
        const wire = new THREE.LineSegments(
            new THREE.EdgesGeometry(geo),
            new THREE.LineBasicMaterial({ color: 0xffffff, linewidth: 2 })
        );
        mesh.add(wire);
        group.add(mesh);
    });
}

function setupEventListeners() {
    // PRZYCISK GENERUJ: wysyła m, n, k do server.js
    document.getElementById('run-btn').onclick = async () => {
        const btn = document.getElementById('run-btn');
        const status = document.getElementById('status');
        
        const payload = {
            m: parseInt(document.getElementById('m').value),
            n: parseInt(document.getElementById('n').value),
            k: parseInt(document.getElementById('k').value)
        };

        status.innerText = "Backend pracuje...";
        btn.disabled = true;

        try {
            const res = await fetch('/run-backend', {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify(payload)
            });
            if (res.ok) {
                currentIdx = 0; // Resetuj indeks po generowaniu
                status.innerText = "Zaktualizowano!";
                await loadJSON(); // Przeładuj widok
            }
        } catch (e) {
            status.innerText = "Błąd serwera!";
        } finally {
            btn.disabled = false;
        }
    };

    // Nawigacja
    document.getElementById('next-btn').onclick = () => {
        if (!allData || allData.partitions.length === 0) return;
        currentIdx = (currentIdx + 1) % allData.partitions.length;
        renderCurrent();
    };
    document.getElementById('prev-btn').onclick = () => {
        if (!allData || allData.partitions.length === 0) return;
        currentIdx = (currentIdx - 1 + allData.partitions.length) % allData.partitions.length;
        renderCurrent();
    };

    // Suwaki przekrojów
    document.getElementById('clip-x').oninput = (e) => clippingPlanes[0].constant = e.target.value;
    document.getElementById('clip-y').oninput = (e) => clippingPlanes[1].constant = e.target.value;
    document.getElementById('clip-z').oninput = (e) => clippingPlanes[2].constant = e.target.value;
}

function animate() {
    requestAnimationFrame(animate);
    controls.update();
    renderer.render(scene, camera);
}

// Skalowanie okna
window.onresize = () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
};