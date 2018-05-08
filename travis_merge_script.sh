if [ "$TRAVIS_BRANCH" != "development" -o "$TRAVIS_PULL_REQUEST" != "false" ]; then
    exit 0;
fi
export GIT_COMMITTER_EMAIL="9caihezi@gmail.com"
export GIT_COMMITTER_NAME="9caihezi"
git config --add remote.origin.fetch +refs/heads/*:refs/remotes/origin/* || exit
git fetch --all || exit
git checkout master || exit
git merge --no-ff "$TRAVIS_COMMIT" || exit
git push https://${GITHUB_TOKEN}@github.com/9caihezi/toolchain.git
