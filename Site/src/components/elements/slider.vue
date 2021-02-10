<template>
    <input ref="slider" class="slider" type="range" min="0" max="255" v-model="inValue"/>
</template>

<script>
export default {
    name: "sliderEl",
    data() {
        return {
            inValue: 128,
            color: "#ff00ff"
        }
    },
    computed: {
        value: function() {
            return 255 - this.inValue;
        }
    },
    methods: {
        changeColor: function(color) {
            this.$refs.slider.style.setProperty("--color", color)
        }
    }
} 
</script>

<style lang="scss" scoped>
    $borderCol: #ccd1d6;
    $height: 44px;

    .slider {
        appearance: none;
        height: $height;
        border-radius: 8px;
        border: 1px solid $borderCol;
        width: 100%;
        transform: rotate(180deg);

        --color: #006CFF;
    }

    .slider:focus {
        outline: none;
    }

    .slider::-moz-range-thumb {
        border: 0.1px solid $borderCol;
        height: $height;
        width: 16px;
        border-radius: 10px;
        background: #ffffff;
        cursor: pointer;
    }

    .slider::-moz-range-progress {
        height: $height;
        background: #ffffff;
        border-radius: 8px 0px 0px 8px;
        cursor: pointer;
    }

    .slider::-moz-range-track {
        cursor: pointer;
        height: $height;
        background: linear-gradient(270deg, #ffffff, var(--color));
        border-radius: 8px;
    }
</style>