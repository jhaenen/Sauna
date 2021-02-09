<template>
    <div id="container"><div id="itemHolder" :class="{lightMode: !(SD.darkMode), darkMode: SD.darkMode}">
        <div :class="{item: true, lightMode: !(SD.darkMode), darkMode: SD.darkMode}">
            <temp-icon class="icon"/>
            <div>
                <div class="title">Temperatuur</div>
                <div class="value">{{SD.sensorData.temp}}&#176;C</div>
            </div>
        </div>
        <div :class="{item: true, lightMode: !(SD.darkMode), darkMode: SD.darkMode}">
            <hum-icon class="icon"/>
            <div>
                <div class="title">Vochtigheid</div>
                <div class="value">{{SD.sensorData.hum}}%</div>
            </div>
        </div>
    </div></div>
</template>

<script>
import Store from "../stores/Store"

import tempIcon from "../assets/temperatuur_icon.svg"
import humIcon from "../assets/vochtigheid_icon.svg"

export default {
    name: "sensorData",
    components: {tempIcon, humIcon},
    data() {
        return {
            SD: Store.data
        }
    },
    mounted() {
        Store.methods.getSensorData();
        setInterval(Store.methods.getSensorData, 5000);
    }
}
</script>

<style scoped>
    #container {
        display: flex;
        justify-content: center;

    }

    #itemHolder {
        width: 100vw;
        
    }

    #itemHolder.lightMode {
        box-shadow: 0 10px 20px rgba(0, 0, 0, 0.1);
    }

    .item.darkMode {
        background: #1d2327;
    }

    .item {
        height: 76px;
        min-width: 173px;
        display: flex;
        align-items: center;
        justify-content: flex-start;
    }

    @media only screen and (min-width: 370px) {
        #itemHolder {
            width: 400px;
            min-width: 366px;
            display: flex;
            align-items: center;
            /* justify-content: space-around; */
            justify-content: space-between;
            margin: 0 16px;
            box-shadow: 0 0 0 rgba(0, 0, 0, 0);
        }

        #itemHolder.lightMode {
            box-shadow: 0 0 0 rgba(0, 0, 0, 0);
        }

        .item {
            margin: 0;
            border-radius: 8px;
        }

        .item.lightMode {
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.1);
        }
    }

    

    .icon {
        width: 48px;
        height: 48px;
        margin: 8px 8px 8px 14px;
    }

    .title {
        font-weight: 600;
        font-size: 14px;
    }

    .value {
        opacity: 40%;
        font-size: 14px;
    }
</style>