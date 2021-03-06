# es6 1 ES6简介

## 1.1 Babel转码器

Babel 是一个广泛使用的 ES6 转码器，可以将 ES6 代码转为 ES5 代码，从而在现有环境执行。除了Babel之外，还有Google的Traceur转码器，也可以将 ES6 代码转为 ES5 代码。

安装Babel

```
$ npm install --save-dev @babel/core
``` 

```js
// 转码前
input.map(item => item + 1);

// 转码后
input.map(function (item) {
  return item + 1;
});
```

### 配置文件.babelrc

Babel 的配置文件是.babelrc，存放在项目的根目录下。基本格式如下

```js
{
  "presets": [],
  "plugins": []
}
```

presets字段设定转码规则，官方提供以下的规则集，你可以根据需要安装。

```
# 最新转码规则
$ npm install --save-dev @babel/preset-env

# react 转码规则
$ npm install --save-dev @babel/preset-react
```

然后加入配置文件

```js
  {
    "presets": [
      "@babel/env",
      "@babel/preset-react"
    ],
    "plugins": []
  }
```

### @babel/cli

Babel 提供命令行工具@babel/cli，用于命令行转码。


```
$ npm install --save-dev @babel/cli
```

基本用法

```
# 转码结果输出到标准输出
$ npx babel example.js

# 转码结果写入一个文件
# --out-file 或 -o 参数指定输出文件
$ npx babel example.js --out-file compiled.js
# 或者
$ npx babel example.js -o compiled.js

# 整个目录转码
# --out-dir 或 -d 参数指定输出目录
$ npx babel src --out-dir lib
# 或者
$ npx babel src -d lib

# -s 参数生成source map文件
$ npx babel src -d lib -s
```

### @babel/node

@babel/node模块的babel-node命令，提供一个支持 ES6 的 REPL 环境。它支持 Node 的 REPL 环境的所有功能，而且可以直接运行 ES6 代码。（REPL是node自带交互式解释器）

```
$ npm install --save-dev @babel/node
$ npx babel-node
> (x => x * 2)(1)
2
```

### @babel/register

@babel/register模块改写require命令，为它加上一个钩子。此后，每当使用require加载.js、.jsx、.es和.es6后缀名的文件，就会先用 Babel 进行转码。需要注意的是，@babel/register只会对require命令加载的文件转码，而不会对当前文件转码。另外，由于它是实时转码，所以只适合在开发环境使用。

```js
// index.js
require('@babel/register');
require('./es6.js'); // es6.js代码 console.log((x => x * 2)(1));
```

```
$ npm install --save-dev @babel/register
$ node index.js
2
```

### babel API

如果某些代码需要调用 Babel 的 API 进行转码，就要使用@babel/core模块。

```js
var babel = require('@babel/core');

// 字符串转码
babel.transform('code();', options);
// => { code, map, ast }

// 文件转码（异步）
babel.transformFile('filename.js', options, function(err, result) {
  result; // => { code, map, ast }
});

// 文件转码（同步）
babel.transformFileSync('filename.js', options);
// => { code, map, ast }

// Babel AST转码
babel.transformFromAst(ast, code, options);
// => { code, map, ast }
```

`options`是配置对象。下面的例子中，transform方法的第一个参数是一个字符串，表示需要被转换的 ES6 代码，第二个参数是转换的配置对象。

```js
var es6Code = 'let x = n => n + 1';
var es5Code = require('@babel/core')
  .transform(es6Code, {
    presets: ['@babel/env']
  })
  .code;

console.log(es5Code);
// '"use strict";\n\nvar x = function x(n) {\n  return n + 1;\n};'
```

### @babel/polyfill

Babel 默认只转换新的 JavaScript 句法（syntax），而不转换新的 API，比如Iterator、Generator、Set、Map、Proxy、Reflect、Symbol、Promise等全局对象，以及一些定义在全局对象上的方法（比如Object.assign）都不会转码。

举例来说，ES6 在Array对象上新增了Array.from方法。Babel 就不会转码这个方法。如果想让这个方法运行，必须使用babel-polyfill，为当前环境提供一个垫片。

```
$ npm install --save-dev @babel/polyfill
```

然后，在脚本头部，加入如下一行代码。

```js
import '@babel/polyfill';
// 或者
require('@babel/polyfill');
```

### @babel/standalone

Babel 也可以用于浏览器环境，使用@babel/standalone模块提供的浏览器版本，将其插入网页。注意，网页实时将 ES6 代码转为 ES5，对性能会有影响。生产环境需要加载已经转码完成的脚本。

```html
<script src="https://unpkg.com/@babel/standalone/babel.min.js"></script>
<script type="text/babel">
// Your ES6 code
</script>
```
