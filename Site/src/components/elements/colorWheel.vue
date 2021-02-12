<template>
    <div id="container" draggable="false">
        <div ref="wheel" id="wheel" class="clickable">
            <div id="inner1" :class="{darkMode: SD.darkMode}">
                <div id="inner2" :class="{darkMode: SD.darkMode}"></div>
            </div>
            <div ref="handle" id="handle" :style="{left: left + 2 + 'px', top: top + 2 + 'px'}"></div>
        </div>
    </div>
</template>

<script>
import Store from "../../stores/Store"

export default {
    name: "colorWheel",
    data() {
        return {
            SD: Store.data,
            left: 0,
            top: 0,
        }
    }, 
    mounted() {
        var handleGrab = false;

        this.left = this.$refs.wheel.offsetWidth / 2 - 2 - 18;
        this.top = 0;

        this.$refs.wheel.addEventListener("pointerdown", (e) => {
            if(e.buttons == 1 && e.target == this.$refs.wheel) {
                const wh = this.$refs.wheel.offsetWidth / 2 - 2 - 18;
                const x = e.layerX - wh - 18;
                const y = wh - e.layerY + 18;;
                const coords = syncCoords(x, y, wh);

                this.left = coords.x;
                this.top = coords.y;
            }
        });

        this.$refs.handle.addEventListener("pointerdown", (e) => {
            if(e.buttons == 1) handleGrab = true;
        });

        window.addEventListener("pointerup", (e) => {
            if(handleGrab) handleGrab = false;
        });

        window.addEventListener("pointermove", (e) => {
            if(handleGrab) {
                var righTarget 
                const wh = this.$refs.wheel.offsetWidth / 2 - 2 - 18;
                var x = e.layerX - wh - 18;
                var y = wh - e.layerY + 18;

                if(e.target == this.$refs.wheel) righTarget = true;
                else if(e.target == this.$refs.handle) {
                    righTarget = true;
                    x += e.target.offsetLeft;
                    y -= e.target.offsetTop;
                };

                if(righTarget) {
                    const coords = syncCoords(x, y, wh);
                    this.left = coords.x;
                    this.top = coords.y;
                }
            }
        });

        function syncCoords(x, y, size) {
            var phi
            if(x == 0) {
                if(y > 0) phi = .5 * Math.PI;
                else phi = 1.5 * Math.PI;
            } else if(y == 0) {
                if(x > 0) phi = 0;
                else phi = Math.PI;
            } 
            else if(x > 0 && y > 0) phi = Math.atan(y / x);
            else if(x < 0 && y > 0) phi = Math.PI - Math.atan(-y / x);
            else if(x < 0 && y < 0) phi = Math.PI + Math.atan(y / x);
            else if(x > 0 && y < 0) phi = 2 * Math.PI - Math.atan(-y / x);

            return { x: size + size * Math.cos(phi), y: size - size * Math.sin(phi), deg: Math.round(phi * (180 / Math.PI)) }
        }
    }
}
</script>

<style lang="scss" scoped>
    $cwh: 260px;
    $wwh: 240px;
    $i1wh: 160px;
    $i2wh: 130px;
    $border: 7px;

    #container {
        position: relative;
        width: $cwh;
        height: $cwh;
        border-radius: 50%;
        background: conic-gradient(
            rgba(0, 255, 255, 0.2) 0deg,
            rgba(0, 64, 255, 0.2) 45deg,
            rgba(128, 0, 255, 0.2) 90deg,
            rgba(255, 0, 191, 0.2) 135deg,
            rgba(255, 0, 0, 0.2) 180deg,
            rgba(255, 191, 0, 0.2) 225deg,
            rgba(128, 255, 0, 0.2) 270deg,
            rgba(0, 255, 64, 0.2) 315deg,
            rgba(0, 255, 255, 0.2) 360deg
        );
    }

    #wheel {
        position: absolute;
        top: ($cwh - $wwh) / 2;
        left: ($cwh - $wwh) / 2;
        width: $wwh;
        height: $wwh;
        border-radius: 50%;
        background: conic-gradient(
            hsl(180, 100%, 50%) 0deg,
            hsl(210, 100%, 50%) 30deg,
            hsl(240, 100%, 50%) 60deg,
            hsl(270, 100%, 50%) 90deg,
            hsl(300, 100%, 50%) 120deg,
            hsl(330, 100%, 50%) 150deg,
            hsl(360, 100%, 50%) 180deg,
            hsl(30, 100%, 50%) 210deg,
            hsl(60, 100%, 50%) 240deg,
            hsl(90, 100%, 50%) 270deg,
            hsl(120, 100%, 50%) 300deg,
            hsl(150, 100%, 50%) 330deg,
            hsl(180, 100%, 50%) 360deg
        );
    }

    #handle {
        position: absolute;
        background: white;
        width: 36px;
        height: 36px;
        border-radius: 50%;
        top: 2px;
        left: $wwh / 2 - 18px;
    }

    #inner1 {
        position: absolute;
        top: ($wwh - $i1wh) / 2;
        left: ($wwh - $i1wh) / 2;
        border-radius: 50%;
        width: $i1wh;
        height: $i1wh;
        background: #ffffff;
        cursor: default;
    }

    #inner1.darkMode {
        background: #1E2327;
    }

    #inner2 {
        position: absolute;
        top: ($i1wh - $i2wh) / 2 - $border;
        left: ($i1wh - $i2wh) / 2 - $border;
        border-radius: 50%;
        width: $i2wh;
        height: $i2wh;
        background: inherit;
        border: $border solid #e4e4e4;
    } 

    #inner2.darkMode {
        border: $border solid #3a3a3a;
    }
</style>