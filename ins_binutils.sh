export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz # If the link 404's, look for a more recent version
tar xf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
#../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix= /usr/local
../binutils-2.24/configure --enable-interwork --disable-dependency-tracking --target=$TARGET --disable-werror --with-readline=`brew --prefix readline` --prefix=$PREFIX 
make all install

