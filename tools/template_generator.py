import os
import re

class template_replacement:
    key: str
    replacement: str

    def __init__( self, tmpl_key: str, tmpl_replacement: str ):
        self.key = tmpl_key
        self.replacement = tmpl_replacement
    
    def get_key_str( self ):
        return str("$(" + self.key + ")")
    
    def get_replacement_str( self ):
        return str(self.replacement)


def replace( self, template: str, filename: str, replacers: list[template_replacement] ):
    template_file: str
    with open(template, 'r') as tmpl:
        template_file = tmpl.read()
        for replacer in replacers:
            tmp = re.sub( replacer.get_key_str(), replacer.get_replacement_str(), template_file )
            template_file = tmp

    with open(filename, 'w') as out:
        out.write(template_file)
