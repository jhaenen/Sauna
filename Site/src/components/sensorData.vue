<template>
    <div id="container"><div id="itemHolder">
        <div class="item">
            <temp-icon class="icon"/>
            <div>
                <div class="title">Temperatuur</div>
                <div class="value">46&#176;C</div>
            </div>
        </div>
        <div class="item">
            <hum-icon class="icon"/>
            <div>
                <div class="title">Vochtigheid</div>
                <div class="value">75%</div>
            </div>
        </div>
    </div></div>
</template>

<script>
import tempIcon from "../assets/temperatuur_icon.svg"
import humIcon from "../assets/vochtigheid_icon.svg"

export default {
    name: "sensorData",
    components: {tempIcon, humIcon}
}
</script>

<style scoped>
    #container {
        display: flex;
        justify-content: center;

    }

    #itemHolder {
        display: flex;
        align-items: center;
        justify-content: space-around;
        width: 600px;
        min-width: 366px;
    }

    .item {
        height: 76px;
        min-width: 173px;
        display: flex;
        align-items: center;
        justify-content: center;
        border-radius: 8px;
        box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
    }

    .icon {
        width: 48px;
        height: 48px;
        margin: 8px;
    }

    .title {
        font-weight: 600;
        font-size: 14px;
        color: #16191C;
    }

    .value {
        color: #16191C;
        opacity: 40%;
        font-size: 14px;
    }
</style>