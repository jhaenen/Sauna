<template>
    <div class="center">
        <div>
            <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                <div :class="{items: true, darkMode: SD.darkMode}">
                    <div class="item title">Lichtsterkte</div>
                    <div class="item"><slider-el color="#ff00ff" /></div>
                </div>
            </div>
            <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                <div :class="{items: true, darkMode: SD.darkMode}">
                    <div class="item title">Kleuren</div>
                    <div class="item center"><color-wheel /></div>
                </div>
            </div>
            <div class="buttonBay">
                <div :class="{itemHolder: true, small: true, center: true, clickable: true, darkMode: SD.darkMode}"><light-icon :class="{icon: true, darkMode: SD.darkMode}"/><div>Wit licht</div></div>
                <div :class="{itemHolder: true, small: true, center: true, clickable: true, darkMode: SD.darkMode}"><scene-icon :class="{icon: true, darkMode: SD.darkMode}"/>Scènes</div>
                <div :class="{itemHolder: true, small: true, center: true, clickable: true, darkMode: SD.darkMode}"><anim-icon :class="{icon: true, darkMode: SD.darkMode}"/>Animaties</div>
            </div>
            <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                <div class="item"><button>Hello</button></div>
            </div>
        </div>
    </div>
</template>

<script>
import Store from "../stores/Store"

import sliderEl from "../components/elements/slider.vue"
import colorWheel from "../components/elements/colorWheel.vue"

import animIcon from "../assets/animatie_icon.svg"
import lightIcon from "../assets/licht_icon.svg"
import sceneIcon from "../assets/scene_icon.svg"

export default {
    name: "Lights",
    components: { sliderEl, colorWheel, animIcon, lightIcon, sceneIcon },
    data() {
        return {
            SD: Store.data
        }
    },
    mounted() {
        Store.data.back = true;
    }
};
</script>

<style lang="scss" scoped>
    .itemHolder {
        box-sizing: border-box;
        margin: 0 0 20px 0;
        max-width: 400px;
        width: calc(100vw - 32px);
        box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
        border-radius: 8px;
        padding: 30px 24px 10px 24px;
    }

    .itemHolder.small {
        align-items: center;
        flex-flow: column;
        width: 114px;
        height: 114px;
        padding: 0px;
        font-size: 14px;
        font-weight: 600;
    }

    .itemHolder.darkMode {
        background: #1E2327;
        box-shadow: 0 0px 0px rgba(0, 0, 0, 0);
    }

    .buttonBay {
        display: flex;
        justify-content: space-between;
    }

    .items {
        width: 100%;
    }

    .items.darkMode {
        background: #1E2327;
        border-radius: 8px;
    }

    .item {
        display: flex;
        padding-bottom: 20px;
    }

    .title {
        font-size: 18px;
        font-weight: 600;
    }

    .icon {
        margin-bottom: 8px;
        background: inherit;
    }

    .icon.darkMode > * {
        stroke: #1E2327;
        fill: white;
    }
    
</style>