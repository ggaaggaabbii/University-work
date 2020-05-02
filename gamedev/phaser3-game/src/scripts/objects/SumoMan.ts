import enable3d, { Scene3D, Canvas, Cameras, ExtendedObject3D } from 'enable3d'

export default class SumoMan {
    x: number;
    y: number;
    player: ExtendedObject3D;
    third: any;
    color: any;
    name: string;
    speed: number;

    constructor(x: number, y: number, gltf: any, third: any, rotationAngle: any, color: any, name: string) {
        this.x = x;
        this.y = y;
        this.third = third;
        this.color = color;
        this.name = name;
        this.speed = 8;

        this.player = this.third.new.extendedObject3D();
        this.player.add(gltf.scene);

        this.player.traverse(child => {
            if (child.type == 'Mesh') {
                child.castShadow = child.receiveShadow = true;
                if (child.name.indexOf("Mawashi") != -1) {
                    // @ts-ignore
                    child.material = this.third.add.material({ standard: { color: this.color, emissive: this.color, roughness: 0.4, metalness: 1, skinning: true } })
                    // @ts-ignore
                    child.material.needsUpdate = true;
                }
                // @ts-ignore
                child.material.roughness = 1;
                // @ts-ignore
                child.material.metalness = 0;
            }
        });

        const scale = 1 / 20;
        this.player.scale.set(scale, scale, scale);

        this.player.position.setY(5);
        this.player.position.setX(this.x);
        this.player.position.setZ(this.y);

        this.third.add.existing(this.player)
        this.player.rotateY(rotationAngle * (Math.PI / 2));
        this.third.physics.add.existing(this.player, { shape: 'box', height: 2.85, width: 1, depth: 1, mass: 1, offset: { y: -1.6 } })
        this.player.body.setLinearFactor(1, 1, 0);
        this.player.body.setAngularFactor(0, 0, 0);
        this.player.body.setFriction(0);

        const sensor = this.third.new.extendedObject3D();
        this.third.physics.add.existing(sensor, { mass: 1e-8, shape: 'box', width: 0.2, height: 0, depth: 0.2 });
        sensor.body.setCollisionFlags(4);
        this.third.physics.add.constraints.lock(this.player.body, sensor.body);

        sensor.body.on.collision((otherObject, event) => {
            if (otherObject.name === 'ring') {
                this.player.userData.onGround = true;
            }
        })
    }

    update() {
        if (this.player.position.y < -2) {
            this.player.userData.dead = true;
        }
    }

    setPositions() {
    }

    moveUp() {
        const theta = this.player.world.theta;

        this.player.body.setVelocityZ(-this.speed);
        this.player.body.setAngularVelocityY(Math.random() * 10);
    }

    moveDown() {
        const theta = this.player.world.theta;

        this.player.body.setVelocityZ(this.speed);
        this.player.body.setAngularVelocityY(Math.random() * 10);
    }

    moveRight() {
        const theta = this.player.world.theta;

        this.player.body.setVelocityX(this.speed);
        this.player.body.setAngularVelocityY(Math.random() * 10);
    }

    moveLeft() {
        const theta = this.player.world.theta;

        this.player.body.setVelocityX(-this.speed);
        this.player.body.setAngularVelocityY(Math.random() * 10);
    }

    randomMove() {
        const m = Math.random();

        if (m < 0.25) {
            this.moveUp();
        } else if (m < 0.5) {
            this.moveDown();
        } else if (m < 0.75) {
            this.moveLeft()
        } else {
            this.moveRight()
        }
    }

    isAlive() {
        return !this.player.userData.dead;
    }

}
