export default class MenuScene extends Phaser.Scene {
    fpsText: Phaser.GameObjects.Text

    constructor() {
        super({ key: 'bootGame' })
    }

    init() {

    }

    preload() {
        this.load.image('background', 'assets/img/sumo-meme.png');
        this.load.image('menu', 'assets/img/MenuButton.png');
        this.load.image('emptyButton', 'assets/img/EmptyButton.png');
    }

    create() {
        let centerWidthPixel = this.game.renderer.width / 2;
        let height = this.game.renderer.height;

        //this.scene.start("playGame")
        this.add.image(0, 0, 'background').setOrigin(0, 0).setDepth(0).setScale(0.68);
        this.add.image(centerWidthPixel, height * 0.3, 'menu').setDepth(1).setScale(0.5);
        let play1Player = this.add.image(centerWidthPixel, height * 0.5, 'emptyButton').setDepth(1).setScale(0.38);
        let play2Players = this.add.image(centerWidthPixel, height * 0.7, 'emptyButton').setDepth(1).setScale(0.38);
        this.add.text(centerWidthPixel - 90, height * 0.46, "1 Player", { font: "50px Arial" });
        this.add.text(centerWidthPixel - 105, height * 0.66, "2 Players", { font: "50px Arial" });

        play1Player.setInteractive();
        play2Players.setInteractive();

        play1Player.on('pointerup', () => {
            this.scene.start("playGame", { players: 1 });
        });

        play2Players.on('pointerup', () => {
            this.scene.start("playGame", { players: 2 });
        });
    }

    update() {

    }
}
