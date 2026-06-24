# [cK] Lily58 Pro Rev1

My personal Lily58 Layout.

    - It uses a couple of generic rp2040. Thus using `elite-c` pin layout.

### First Time Setup

- Setup [QMK](https://docs.qmk.fm/newbs_getting_started)
    - Install QMK however you want, as long as you can run below commands:
        - Run: `qmk setup`
        - Run: `qmk compile`
- Create 'ck' Layout
    - Run: `qmk new-keymap -kb lily58/rev1 -km ck`

### Compile
```sh
qmk compile -kb lily58/rev1 -km ck
```

### Firmware locations
    ~/qmk_firmware/keyboards/lily58/keymaps/ck/


## Troubleshooting

- `Converting from 'elite_c ' to 'rp2040_ce' not possible!`
    - Check `rules.mk` make sure no extra spaces are in that line (i.e. end line comments).
