#!/bin/bash -x
chroots=""
tests=""
#blend_pixel blend_mask_color blend_color blend_pixel_color blend_mask_pixel"

for dir in $chroots; do
   for t in $tests; do
     mkdir -p $dir/test
     rm -rf $dir/test/$t
     cp -r $t $dir/test/
     chroot $dir bash -c "cd /test/$t; make;" || exit 1
     chroot $dir bash -c "cd /test/$t; make check -k;"
   done
done

