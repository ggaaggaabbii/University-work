import 'phaser'
import GameScene from './scenes/GameScene'
import MenuScene from './scenes/MenuScene'
import enable3d, { Canvas, Scene3D } from 'enable3d'

const DEFAULT_WIDTH = 1280
const DEFAULT_HEIGHT = 720

const config = {
    type: Phaser.WEBGL,
    backgroundColor: '#ffffff',
    scale: {
        mode: Phaser.Scale.FIT,
        autoCenter: Phaser.Scale.CENTER_BOTH,
        width: DEFAULT_WIDTH,
        height: DEFAULT_HEIGHT
    },
    scene: [MenuScene, GameScene],
    ...Canvas()
}

window.addEventListener('load', () => {
    enable3d(() => new Phaser.Game(config)).withPhysics('/assets')
})
