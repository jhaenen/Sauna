const VueLoaderPlugin = require('vue-loader/lib/plugin');

module.exports = {
    entry: {
        app: './src/index.js',
    },
    module: {
        rules: [
        {
            test: /\.vue$/,
            loader: 'vue-loader'
        },
        {
            test: /\.js$/,
            exclude: /node_modules/,
            loader: 'babel-loader'
        },
        {
            test: /\.svg$/,
            use: ['babel-loader', 'vue-svg-loader'],
        }
        ]
    },
    plugins: [
        new VueLoaderPlugin()
    ]
};