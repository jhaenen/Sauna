const VueLoaderPlugin = require('vue-loader/lib/plugin');
var path = require('path');

module.exports = {
  target: "web",
  mode: 'development',
  devServer: {
    contentBase: path.join(__dirname, 'dev'),
    port: 1000,
    hot: true,
    open: true,
    historyApiFallback: true
  },
  devtool: "eval-source-map",
  module: {
    rules: [
      {
        test: /\.vue$/,
        loader: 'vue-loader'
      },
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader',
      },
      {
        test: /\.css$/,
        use: [
          'style-loader',
          'css-loader'
        ]
      },
      {
        test: /\.s[ac]ss$/i,
        use: [
          "style-loader",
          "css-loader",
          "sass-loader",
        ],
      },
      {
        test: /\.svg$/,
        use: ['babel-loader', 'vue-svg-loader'],
      }
    ]
  },
  plugins: [
    new VueLoaderPlugin(),
  ]
};