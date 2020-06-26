/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/alg/alg.h"
#include "libc/alg/arraylist.h"
#include "libc/mem/mem.h"
#include "libc/runtime/runtime.h"
#include "libc/str/str.h"
#include "libc/testlib/testlib.h"

struct string {
  size_t i, n;
  char *p;
};

struct string16 {
  size_t i, n;
  char16_t *p;
};

struct ArrayListInteger {
  size_t i, n;
  int *p;
};

TEST(append, worksGreatForScalars) {
  char c = 'a';
  struct string s;
  memset(&s, 0, sizeof(s));
  for (size_t i = 0; i < 1024; ++i) ASSERT_EQ(i, append(&s, &c));
  ASSERT_EQ(1024, s.i);
  for (size_t i = 0; i < s.i; ++i) ASSERT_EQ('a', s.p[i]);
  free_s(&s.p);
}

TEST(append, isGenericallyTyped) {
  int c = 0x31337;
  struct ArrayListInteger s;
  memset(&s, 0, sizeof(s));
  for (size_t i = 0; i < 1024; ++i) ASSERT_EQ(i, append(&s, &c));
  ASSERT_EQ(1024, s.i);
  ASSERT_GT(malloc_usable_size(s.p), 1024 * sizeof(int));
  for (size_t i = 0; i < s.i; ++i) ASSERT_EQ(0x31337, s.p[i]);
  free_s(&s.p);
}

TEST(concat, worksGreatForStrings) {
  const char *ks =
      "Und wird die Welt auch in Flammen stehen\n"
      "Wir werden wieder auferstehen\n";
  struct string s;
  memset(&s, 0, sizeof(s));
  ASSERT_EQ(0, concat(&s, ks, strlen(ks)));
  ASSERT_EQ(strlen(ks), concat(&s, ks, strlen(ks) + 1));
  ASSERT_STREQ(
      "Und wird die Welt auch in Flammen stehen\n"
      "Wir werden wieder auferstehen\n"
      "Und wird die Welt auch in Flammen stehen\n"
      "Wir werden wieder auferstehen\n",
      s.p);
  ASSERT_EQ(strlen(ks) * 2 + 1, s.i);
  free_s(&s.p);
}

TEST(concat, isGenericallyTyped) {
  const char16_t *ks =
      u"Drum hoch die Fäuste, hoch zum Licht.\n"
      u"Unsere schwarzen Seelen bekommt ihr nicht.\n";
  struct string16 s;
  memset(&s, 0, sizeof(s));
  ASSERT_EQ(0, concat(&s, ks, strlen16(ks)));
  ASSERT_EQ(strlen16(ks), concat(&s, ks, strlen16(ks) + 1));
  ASSERT_STREQ(
      u"Drum hoch die Fäuste, hoch zum Licht.\n"
      u"Unsere schwarzen Seelen bekommt ihr nicht.\n"
      u"Drum hoch die Fäuste, hoch zum Licht.\n"
      u"Unsere schwarzen Seelen bekommt ihr nicht.\n",
      s.p);
  ASSERT_EQ(strlen16(ks) * 2 + 1, s.i);
  free_s(&s.p);
}