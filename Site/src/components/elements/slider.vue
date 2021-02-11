<template>
    <div ref="slider" :class="{slider: true, darkMode: SD.darkMode}" draggable="false">
        <div ref="sliderHandle" class="handle" :style="{left: left + 'px'}"></div>
        <div ref="progress" :class="{progress: true, darkMode: SD.darkMode}" :style="{width: progressWidth + 'px'}"></div>
    </div>
</template>

<script>
import Store from "../../stores/Store"

export default {
    name: "sliderEl",
    props: ['color'],
    data() {
        return {
            SD: Store.data,
            left: -2,
            isMounted: false
        }
    },
    mounted() {
        var handleGrab = false;
        var resizing = false;
        var resizeVal = 0;

        window.addEventListener("resize", () => {
            if(!resizing) {
                resizeVal = this.value;
                resizing = true;
            }
            this.left = resizeVal * (this.$refs.slider.offsetWidth - 18) / 100 - 2;
        });

        window.addEventListener("pointerdown", (e) => {
            resizing = false;
        });

        this.$refs.slider.addEventListener("pointerdown", (e) => {
            if(e.buttons == 1 && e.target == this.$refs.slider) {
                this.left = e.layerX - 8;
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
        this.left = (this.$refs.slider.offsetWidth - 16) / 2;
        this.$refs.slider.style.setProperty("--color", this.color)
    },
    computed: {
        value: function() {
            if(!(this.isMounted)) return 0;
            else return Math.round((this.left + 2) * 100 / (this.$refs.slider.offsetWidth - 14));
        },
        progressWidth: function() {
            if(!(this.isMounted)) return 0;
            else return this.$refs.slider.offsetWidth - 16 - this.left + 8;
        } 
    },
    // methods: {
    //     changeColor: function(color) {
    //         this.$refs.slider.style.setProperty("--color", color)
    //     }
    // }
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