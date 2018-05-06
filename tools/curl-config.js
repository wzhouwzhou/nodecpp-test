const { exec } = require('child_process');

const argv = process.argv;

if (!argv[2]) {
  console.error('Missing argument to curl-config');
  process.exit(1);
}

const arg = argv[2].trim();

exec(`curl-config ${arg}`, (err, stdout, stderr) => {
  if (err != null) {
    console.error('Could not run curl-config.');
    console.error('Output: ' + stderr);
    process.exit(1);
  }

  console.log(stdout);
  process.exit(0);
});
