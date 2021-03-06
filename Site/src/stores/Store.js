var gateway = "ws://192.168.2.234/websocket";
var websocket;

const Store = {
    data: {
        darkMode: false,
        back: false,
        sensorData: { temp: "--", hum: "--" },
        lightInfo: { color: { h: 128, v: 128, w: 128 }, onOff: false, speed: 50, whiteMode: false, fan: false },
        connection: true
    },
    methods: {
        initWebSocket() {
            websocket = new WebSocket(gateway);
            websocket.onmessage = (e) => {
                const data = JSON.parse(e.data);
                console.log(data);
                if(data.sensor != undefined) Store.data.sensorData = data.sensor;
                if(data.lights != undefined) Store.data.lightInfo = data.lights;
            }
        },
        updateLights() {
            var lightInfo = {lights: Store.data.lightInfo};
            websocket.send(JSON.stringify(lightInfo));
        }
    }
};

export default Store;