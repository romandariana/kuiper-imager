# -- Import setup -------------------------------------------------------------

from os import path
import os

# -- Project information ------------------------------------------------------

repository = 'kuiper-imager'
project = 'Kuiper Imager'
copyright = '2025, Analog Devices, Inc.'
author = 'Analog Devices, Inc.'

# Version from environment variable or fallback
version = os.environ.get('ADOC_DOC_VERSION', 'latest')

# -- General configuration ----------------------------------------------------

extensions = [
    'sphinx.ext.todo',
    'adi_doctools',
]

needs_extensions = {
    'adi_doctools': '0.3.47'
}

exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
source_suffix = '.rst'

# -- Numbered references configuration ----------------------------------------

numfig = True
numfig_format = {
    'figure': 'Figure %s',
    'table': 'Table %s',
    'code-block': 'Listing %s',
    'section': 'Section %s'
}

# -- External docs configuration ----------------------------------------------

interref_repos = []

# -- Custom extensions configuration ------------------------------------------

hide_collapsible_content = True
validate_links = False

# -- todo configuration -------------------------------------------------------

# The skeleton pages carry `.. todo::` markers naming the source to lift into
# each page (docs Goal 2). Render them so the skeleton is reviewable, but do NOT
# emit warnings for them — otherwise the strict `-W` CI build would fail while
# the pages are still stubs. Flip `todo_emit_warnings` back on once the pages
# are populated and the todos are gone.
todo_include_todos = True
todo_emit_warnings = False

# -- Options for HTML output --------------------------------------------------

html_theme = 'cosmic'
html_static_path = ['resources']
html_favicon = path.join("resources", "icon.png")

html_theme_options = {
    "light_logo": "logo_light.png",
    "dark_logo": "logo_dark.png",
}
