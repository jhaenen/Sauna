import Vue from "vue"
import App from "./app.vue"
import _ from "lodash"

Vue.prototype._ = _

new Vue({
    render: (createEL) => createEL(App)
}).$mount("#app");