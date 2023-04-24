#-----------------------------------------------------------------------------
# ergohaven
#-----------------------------------------------------------------------------

VIAL_ENABLE = yes
QMK_SETTINGS = no

#-----------------------------------------------------------------------------
# getreuer
#-----------------------------------------------------------------------------
# https://github.com/getreuer/qmk-keymap

# SRC += features/achordion.c
# SRC += features/autocorrection.c
# SRC += features/custom_shift_keys.c
SRC += features/caps_word.c
SRC += features/select_word.c
SRC += features/custom_shift_keys.c

#-----------------------------------------------------------------------------
# sunaku
#-----------------------------------------------------------------------------

# https://docs.qmk.fm/#/feature_caps_word?id=caps-word
# disable this because we're using getreuer's latest version in the SRC above
CAPS_WORD_ENABLE = no

# https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-execution
DEFERRED_EXEC_ENABLE = yes

# https://github.com/qmk/qmk_firmware/issues/19593#issuecomment-1387476045
NO_USB_STARTUP_CHECK = yes
