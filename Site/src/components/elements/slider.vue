<template>
    <div touch-action="none" ref="slider" :class="{slider: true, darkMode: SD.darkMode}" draggable="false">
        <div ref="sliderHandle" class="handle" :style="{left: left + 'px'}"></div>
        <div ref="progress" :class="{progress: true, darkMode: SD.darkMode}" :style="{width: progressWidth + 'px'}"></div>
    </div>
</template>

<script>
import Store from "../../stores/Store"

export default {
    name: "sliderEl",
    data() {
        return {
            SD: Store.data,
            left: -2,
            isMounted: false,
            resizing: false
        }
    },
    mounted() {
        var handleGrab = false;
        var resizeVal = 0;

        window.addEventListener("resize", () => {
            if(!this.resizing) {
                resizeVal = this.map(this.currentValue, 0, 255, 0, 101);
                this.resizing = true;
            }
            this.setValue(resizeVal);
        });

        window.addEventListener("pointerdown", (e) => {
            this.resizing = false;
        });

        this.$refs.slider.addEventListener("pointerdown", (e) => {
            if(e.buttons == 1 && e.target == this.$refs.slider) {
                this.left = e.layerX - 8;
                handleGrab = true;
            }
        });

        this.$refs.sliderHandle.addEventListener("pointerdown", (e) => {
            if(e.buttons == 1) {
                handleGrab = true;
            }
        });

        this.$refs.sliderHandle.addEventListener("pointerup", (e) => {
            if(e.buttons == 1) {
                handleGrab = false;
            }
        });

        window.addEventListener("selectstart", (e) => {
            if(handleGrab) {
                e.preventDefault();
            }
        });

        window.addEventListener("pointermove", (e) => {
            if(e.buttons == 1 && handleGrab && this.$refs.slider !== undefined && this.$refs.sliderHandle !== undefined) {
                if(e.target == this.$refs.slider) {
                    this.left = e.layerX - 8;
                } else if(e.target == this.$refs.sliderHandle) {
                    this.left = e.layerX + e.target.offsetLeft - 8;
                }
                if(this.left > (this.$refs.slider.offsetWidth - 16)) this.left = this.$refs.slider.offsetWidth - 16;
                if(this.left < -2) this.left = -2;
            }
        });

        this.isMounted = true;
        this.setValue(this.map(this.currentValue, 0, 255, 0, 101));
        this.$refs.slider.style.setProperty("--color", "hsl(" + this.map(Store.data.lightInfo.color.h, 0, 255, 0, 360) + ", 100%, 50%)");
    },
    methods: {
        setValue: function(value) {
            if(this.isMounted) this.left = value * (this.$refs.slider.offsetWidth - 18) / 100 - 2;
        },
        map: function(x, in_min, in_max, out_min, out_max) {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }
    },
    computed: {
        progressWidth: function() {
            if(!(this.isMounted)) return 0;
            else return this.$refs.slider.offsetWidth - 16 - this.left + 8;
        },
        currentHue() {
            return Store.data.lightInfo.color.h;
        },
        currentValue() {
            return Store.data.lightInfo.color.v;
        },
        currentWhite() {
            return Store.data.lightInfo.color.w;
        },
        whiteMode() {
            return Store.data.lightInfo.whiteMode;
        }
    },
    watch: {
        currentHue: function () {
            if(this.isMounted) {
                if(!(this.whiteMode)) this.$refs.slider.style.setProperty("--color", "hsl(" + this.map(this.currentHue, 0, 255, 0, 360) + ", 100%, 50%)");
            }
        },
        currentValue: function () {
            if(!this.whiteMode) {
                const adj = this.map(this.currentValue, 0, 255, 0, 101);
                this.setValue(adj);
            }
        },
        currentWhite: function () {
            if(this.whiteMode) {
                const adj = this.map(this.currentWhite, 0, 255, 0, 101);
                this.setValue(adj);
            }
        },
        left: function() {
            if(this.isMounted && !(this.resizing)) {
                if(this.whiteMode) Store.data.lightInfo.color.w =  Math.round(this.map(this.left, -2, this.$refs.slider.offsetWidth - 16, 0, 255));
                else Store.data.lightInfo.color.v =  Math.round(this.map(this.left, -2, this.$refs.slider.offsetWidth - 16, 0, 255));
            }
        },
        whiteMode: function() {
            if(this.whiteMode) {
                this.$refs.slider.style.setProperty("--color", "#F1DFB4");
                const adj = this.map(this.currentWhite, 0, 255, 0, 101);
                this.setValue(adj);
            } else {
                this.$refs.slider.style.setProperty("--color", "hsl(" + this.map(this.currentHue, 0, 255, 0, 360) + ", 100%, 50%)");
                const adj = this.map(this.currentValue, 0, 255, 0, 101);
                this.setValue(adj);
            }
        }
    }
} 
</script>

<style lang="scss" scoped>
    $borderCol: #ccd1d6;
    $borderDark: #2f3438;
    $height: 44px;

    .slider {
        // box-sizing: border-box; 
        position: relative;
        height: $height + 1px;
        border-radius: 8px;
        border: 1px solid $borderCol;
        width: 100%;
        background: linear-gradient(90deg, #ffffff, var(--color));

        --color: #006CFF;
        cursor: pointer;
    }

    .slider.darkMode {
        background: linear-gradient(90deg, #1E2327, var(--color));
        border: 1px solid $borderDark;
    }

    .handle {
        position: absolute;
        left: calc(1% - 16px);
        border: 0.1px solid $borderCol;
        height: $height;
        width: 16px;
        border-radius: 10px;
        background: #ffffff;
        cursor: pointer;
        z-index: 1;
    }

    .progress {
        height: $height + 1px;
        background: #ffffff;
        float: right;
        border-radius: 0px 6px 6px 0px;
        cursor: pointer;
        pointer-events: none;
    }

    .progress.darkMode {
        background: #1E2327;
    }
</style>