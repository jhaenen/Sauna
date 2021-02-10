<template>
    <div class="center">
        <div>
            <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                <div :class="{items: true, darkMode: SD.darkMode}">
                    <div class="item title">Lichtsterkte</div>
                    <div class="item"><slider-el/></div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import Store from "../stores/Store"

import sliderEl from "../components/elements/slider.vue"

export default {
    name: "Lights",
    components: { sliderEl },
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
        margin: 20px 0;
        max-width: 400px;
        width: calc(100vw - 32px);
        box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
        border-radius: 8px;
        padding: 30px 24px 10px 24px;
    }

    .itemHolder.darkMode {
        background: #1d2327;
        box-shadow: 0 0px 0px rgba(0, 0, 0, 0);
    }

    .items {
        width: 100%;
    }

    .items.darkMode {
        background: #1d2327;
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
</style>