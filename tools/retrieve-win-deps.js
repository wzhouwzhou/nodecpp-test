// See https://github.com/JCMais/node-libcurl/blob/develop/tools/retrieve-win-deps.js

if (process.platform !== 'win32') {
  process.exit(0);
}

const { exec } = require('child_process'),
  path = require('path'),
  fs = require('fs');

const execConfig = { cwd: path.resolve(`${__dirname}/..}`) },
  depsGypTarget = 'curl-for-windows/curl.gyp:libcurl',
  fileWithDepsTag = 'LIBCURL_VERSION_WIN_DEPS',
  depsRepo = 'https://github.com/JCMais/curl-for-windows.git',
  envCurlForWindowsDepsVersionTag = process.env.NODE_LIBCURL_WINDEPS_TAG;

exec('git rev-parse --show-toplevel', execConfig, (err, stdout) => {
  if (!err && path.relative(execConfig.cwd, stdout.trim()) === '') {
    replaceTokensOnGypFiles(path.resolve(__dirname, '..', 'deps', 'curl-for-windows'));
    process.stdout.write(`deps/${depsGypTarget}`);
  } else {
    retrieveWinDeps();
  }
});

const retrieveWinDeps = () => {
  let depsTag;
  const fileExists = fs.existsSync(fileWithDepsTag);

  if (!fileExists && !envCurlForWindowsDepsVersionTag) {
    console.error(`File: ${fileWithDepsTag} not found, and no NODE_LIBCURL_WINDEPS_TAG environment variable found.`);
    return process.exit(1);
  }

  depsTag = envCurlForWindowsDepsVersionTag ? envCurlForWindowsDepsVersionTag.trim() : fs
    .readFileSync(fileWithDepsTag)
    .toString()
    .replace(/\n|\s/g, '');

  exec(`git clone --branch ${depsTag} ${depsRepo}`, execConfig, err => {
    if (err) {
      if (err.toString().includes('already exists and is not an empty directory')) {
        exec('rmdir curl-for-windows /S /Q', execConfig, err => {
          if (err) {
            console.error(err.toString());
            process.exit(1);
          }

          retrieveWinDeps();
        });
      } else {
        console.error(err.toString());
        process.exit(1);
      }
    } else {
      exec('cd curl-for-windows && git submodule update --init && python configure.py', execConfig, err => {
        if (err) {
          console.error(err.toString());
          process.exit(1);
        }

        replaceTokensOnGypFiles(path.resolve(__dirname, '..', 'curl-for-windows'));

        exec('rmdir curl-for-windows\\.git /S /Q', execConfig, (err) => {
          if (err) {
            console.error(err.toString());
            process.exit(1);
          }

          process.stdout.write(depsGypTarget);
        });
      });
    }
  });
};

const replaceTokensOnGypFiles = dir => {
  let filesToCheck = ['libssh2.gyp', 'openssl/openssl.gyp', 'zlib.gyp', 'curl.gyp'],
    search = /<\(library\)/g,
    replacement = 'static_library',
    i = 0,
    len = filesToCheck.length,
    file;

  while (i < len) replaceOnFile(path.resolve(dir, filesToCheck[i++]), search, replacement);
};

const replaceOnFile = (file, search, replacement) => {
  let fileContent;

  if (!fs.existsSync(file)) {
    console.error(`File: ${file} not found.`);
    process.exit(1);
  }

  fileContent = fs.readFileSync(file).toString().replace(search, replacement);

  fs.writeFileSync(file, fileContent);
};
