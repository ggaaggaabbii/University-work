import SumoMan from '../objects/SumoMan'
import enable3d, { Scene3D, Canvas, Cameras, ExtendedObject3D } from 'enable3d'

export default class GameScene extends Scene3D {
    noPlayers: number;
    redScore: any;
    greenScore: any;
    yellowScore: any;
    blueScore: any;
    redText: Phaser.GameObjects.Text;
    yellowText: Phaser.GameObjects.Text;
    greenText: Phaser.GameObjects.Text;
    blueText: Phaser.GameObjects.Text;
    ringCylinder: any;
    players: any[];
    keys: any;
    human: SumoMan;
    human2: SumoMan;

    constructor() {
        super('playGame');
        this.redScore = 0;
        this.greenScore = 0;
        this.yellowScore = 0;
        this.blueScore = 0;
    }

    init(data) {
        this.requestThirdDimension();
        this.noPlayers = data.players;
    }

    preload() {
        this.load.binary('sumoMan', '/assets/glb/man/sumo_man.gltf');
        this.load.binary('sumoRing', '/assets/glb/ring/sumo_ring.gltf');
        this.load.image('sky', '/assets/img/RingBackground.png');
    }

    create() {
        this.setupCameras();
        this.setupSky();
        this.setupScoreBoard();
        this.setupRing();
        this.setupPlayers();
        this.setupKeys();

        //this.third.physics.debug.enable()
    }

    setupCameras() {

        this.accessThirdDimension({ gravity: { x: 0, y: -20, z: 0 } });

        this.third.warpSpeed('-ground', '-sky', '-orbitControls');

        this.third.renderer.gammaFactor = 1.2;

        this.third.camera.position.set(0, 5, 20);
        this.third.camera.lookAt(0, 0, 0);
    }

    setupSky() {
        const sky = this.add.image(this.cameras.main.width / 2, this.cameras.main.height / 2, 'sky');
        const scaleX = this.cameras.main.width / sky.width;
        const scaleY = this.cameras.main.height / sky.height;
        const scale = Math.max(scaleX, scaleY);
        sky.depth = -1;
        sky.setScale(scale).setScrollFactor(0);
    }

    setupScoreBoard() {
        const w = this.cameras.main.width / 4;
        const h = 30;

        this.yellowText = this.add.text(0 * w + w / 8, h, 'score: ' + this.yellowScore, { fontSize: '32px', fill: 'yellow' })
        this.blueText = this.add.text(1 * w + w / 8, h, 'score: ' + this.blueScore, { fontSize: '32px', fill: 'blue' })
        this.greenText = this.add.text(2 * w + w / 8, h, 'score: ' + this.greenScore, { fontSize: '32px', fill: 'green' })
        this.redText = this.add.text(3 * w + w / 8, h, 'score: ' + this.redScore, { fontSize: '32px', fill: 'red' })

        this.yellowText.depth = 1;
        this.greenText.depth = 1;
        this.blueText.depth = 1;
        this.redText.depth = 1;
    }

    setupRing() {
        this.third.load.gltf('sumoRing', gltf => {
            let ring = this.third.new.extendedObject3D();
            ring.add(gltf.scene);

            const scale = 3;
            ring.scale.set(scale, scale, scale);
            ring.position.setX(0);
            ring.position.setY(0);
            ring.position.setZ(0);

            //WARNING: FOR SOME REASON CYLINDERS CAN'T BE GROUND
            // the length remains 1
            //this.ringCylinder = this.third.add.cylinder({
            //    x: 0,
            //    y: 0,
            //    z: 0,
            //    radiusTop: 12,
            //    radiusBottom: 12,
            //    collisionFlag: 1,
            //    height: 1
            //})
            this.ringCylinder = this.third.add.box({
                x: 0,
                y: 0,
                z: 0,
                width: 20,
                depth: 20,
                height: 1,
            });

            this.ringCylinder.visible = false;
            this.ringCylinder.name = 'ground';
            this.ringCylinder.receiveShadow = this.ringCylinder.castShadow = true;
            this.ringCylinder.material.roughness = 1;
            this.ringCylinder.material.metalness = 1;

            this.third.add.existing(ring);
            this.third.physics.add.existing(ring, { depth: 24, mass: 0 });

            this.third.add.existing(this.ringCylinder);
            this.third.physics.add.existing(this.ringCylinder, { mass: 0 });
        })
    }

    setupPlayers() {
        var redP, blueP, greenP, yellowP;
        this.players = [];

        this.third.load.gltf('sumoMan', gltf => {
            redP = new SumoMan(-10, 0, gltf, this.third, 1, '#BC2A32', 'red');
            this.human = redP;
        })
        this.third.load.gltf('sumoMan', gltf => {
            greenP = new SumoMan(0, -10, gltf, this.third, 0, 'green', 'green');
            this.players.push(greenP);
        })
        this.third.load.gltf('sumoMan', gltf => {
            blueP = new SumoMan(10, 0, gltf, this.third, 3, 'blue', 'blue');
            if (this.noPlayers == 2) {
                this.human2 = blueP;
            } else {
                this.players.push(blueP);
            }
        })
        this.third.load.gltf('sumoMan', gltf => {
            yellowP = new SumoMan(0, 10, gltf, this.third, 2, '#F0FA18', 'yellow');
            this.players.push(yellowP);
        })
    }

    setupKeys() {
        this.keys = {
            w: this.input.keyboard.addKey('w'),
            a: this.input.keyboard.addKey('a'),
            d: this.input.keyboard.addKey('d'),
            s: this.input.keyboard.addKey('s'),
            up: this.input.keyboard.addKey('up'),
            down: this.input.keyboard.addKey('down'),
            left: this.input.keyboard.addKey('left'),
            right: this.input.keyboard.addKey('right')
        }
    }

    update(time, delta) {
        if (!this.ringCylinder || !this.ringCylinder.body) {
            return;
        }

        if (this.players.length == 0) {
            return;
        }

        for (var i = 0; i < this.players.length; i++) {
            if (!this.players[i].player || !this.players[i].player.body) {
                return;
            }
        }

        if (!this.human || !this.human.player || !this.human.player.body) {
            return;
        }

        this.updatePlayers(time);
        this.checkGameState();
    }

    updatePlayers(time: number) {
        this.human.player.body.setAngularVelocityY(0);

        if (time % 6 == 0) {
            for (var i = 0; i < this.players.length; i++) {
                this.players[i].player.body.setAngularVelocityY(0);
                this.players[i].randomMove();
            }
        }

        if (this.keys.d.isDown) {
            this.human.moveRight();
        }
        if (this.keys.a.isDown) {
            this.human.moveLeft();
        }
        if (this.keys.s.isDown) {
            this.human.moveDown();
        }
        if (this.keys.w.isDown) {
            this.human.moveUp();
        }

        if (this.noPlayers == 2) {
            if (this.keys.up.isDown) {
                this.human2.moveUp();
            }
            if (this.keys.down.isDown) {
                this.human2.moveDown();
            }
            if (this.keys.left.isDown) {
                this.human2.moveLeft();
            }
            if (this.keys.right.isDown) {
                this.human2.moveRight();
            }
        }

        for (var i = 0; i < this.players.length; i++) {
            this.players[i].update();
        }

        this.human.update()

        if (this.noPlayers == 2) {
            this.human2.update()
        }
    }

    checkGameState() {
        var activePlayers = 0;

        if (this.human.isAlive()) {
            activePlayers++;
        }

        if (this.noPlayers == 2 && this.human2.isAlive()) {
            activePlayers++;
        }

        for (var i = 0; i < this.players.length; i++) {
            if (this.players[i].isAlive()) {
                activePlayers++;
            }
        }

        if (activePlayers == 1) {
            if (this.human.isAlive()) {
                this.redScore++;
            }

            if (this.noPlayers == 2 && this.human2.isAlive()) {
                this.blueScore++;
            }

            for (var i = 0; i < this.players.length; i++) {
                if (this.players[i].isAlive()) {
                    if (this.players[i].name == "blue") {
                        this.blueScore++;
                    } else if (this.players[i].name == "yellow") {
                        this.yellowScore++;
                    } else {
                        this.greenScore++;
                    }
                }
            }

            this.scene.restart();
        }

        if (activePlayers == 0) {
            console.log("0 players");
        }
    }
}
