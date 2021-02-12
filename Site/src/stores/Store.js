const Store = {
    data: {
        darkMode: false,
        back: false,
        sensorData: { temp: "--", hum: "--" },
        lightInfo: { color: { h: 128, v: 128, w: 128 }, onOff: false, speed: 50, whiteMode: false },
        connection: true
    },
    methods: {
        timeOutHandler() {
            alert("Failed to connect");
            Store.data.connection = false;
        },
        getSensorData() {
            if(Store.data.connection) {
                var xhr = new XMLHttpRequest();   

                xhr.onreadystatechange = function() {
                    if (xhr.readyState === 4 && this.status == 200) {
                        const data = JSON.parse(xhr.response);
                        console.log(data);
                        Store.data.sensorData = data;
                    }
                }

                xhr.ontimeout = Store.methods.timeOutHandler;

                xhr.timeout = 5000;
                xhr.open("GET", "http://192.168.2.233/stats", true);  
                xhr.send(null);
            }
        }
    }
};

export default Store;