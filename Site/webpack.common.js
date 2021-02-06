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
            test: /\.html$/,
            use: 'html-loader'
        },
        {
            test: /\.(png|jpg|gif)$/,
            use: {
                loader: 'file-loader',
                options: {
                name: '[name].[hash].[ext]',
                outputPath: 'img',
                esModule: false
                }
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