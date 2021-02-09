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
            loader: 'babel-loader',
            options: {
            presets: [
                '@babel/preset-env'
            ]
            }
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