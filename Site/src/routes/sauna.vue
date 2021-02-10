<template>
    <div>
        <sensor-data/>
        <div class="center">
            <div>
                <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                    <div :class="{items: true, darkMode: SD.darkMode}">
                        <div class="item"><on-off title="Sauna heaters" :onLink="domoPre + 'switchscene&idx=4&switchcmd=On'" :offLink="domoPre + 'switchscene&idx=4&switchcmd=Off'" :bold="true"/></div>
                        <div><div class="txt clickable" @click="expanded = !expanded"><triangle-icon :class="{triangle: true, rotated: expanded, darkMode: SD.darkMode}"/>4 apparaten</div></div>
                        <div :class="{items: true, darkMode: SD.darkMode}" v-if="expanded">
                            <div class="item" v-for="(lamp, index) in lamps" :key="index"><on-off :title="lamp.name" :onLink="domoPre + lamp.on" :offLink="domoPre + lamp.off" :bold="false"/></div>
                        </div>
                    </div>
                </div>

                <div :class="{itemHolder: true, center: true, darkMode: SD.darkMode}">
                    <div class="items item"><on-off title="Sauna ventilator" :bold="true"/></div>
                </div>
            </div>
        </div>   
    </div>
</template>

<script>
import Store from "../stores/Store"

import sensorData from "../components/sensorData.vue"
import onOff from "../components/onOff.vue" 

import triangleIcon from "../assets/triangle.svg"

export default {
    name: "Sauna",
    components: { onOff, triangleIcon, sensorData },
    data() {
        return {
            SD: Store.data,
            expanded: false,
            domoPre: "http://wolleserver.local:8080/json.htm?type=command&param=",
            lamps: [{name: "Heater rug links", on:"switchlight&idx=525&switchcmd=On", off: "switchlight&idx=525&switchcmd=Off"},
            {name: "Heater rug rechts", on:"switchlight&idx=526&switchcmd=On", off: "switchlight&idx=526&switchcmd=Off"},
            {name: "Heater raam", on:"switchlight&idx=528&switchcmd=On", off: "switchlight&idx=528&switchcmd=Off"}, 
            {name: "Heater plafond", on:"switchlight&idx=524&switchcmd=On", off: "switchlight&idx=524&switchcmd=Off"}]
        }
    },
    mounted() {
        Store.data.back = true;
    }
};
</script>

<style lang="scss" scoped>
    .itemHolder {
        margin: 20px 0;
        max-width: 400px;
        width: calc(100vw - 32px);
        min-width: 270px;
        box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
        border-radius: 8px;
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
        padding: 0 24px;
    }

    .items > :not(:last-child)  {
        border-bottom: 1px solid rgba(22, 25, 28, 0.1);
    }

    .items.darkMode > :not(:last-child)  {
        border-bottom: 1px solid rgba(255, 255, 255, 0.1);
    }

    .txt {
        display: inline-flex;
        align-items: center;
        margin: 2px 0 3px 16px;
        font-size: 14px;
    }

    .triangle {
        margin-right: 8px;
    }

    .triangle.rotated {
        transform: rotate(90deg);
    }

    .triangle.darkMode > * {
        stroke: #ffffff;
        fill: #ffffff;
    }
</style>