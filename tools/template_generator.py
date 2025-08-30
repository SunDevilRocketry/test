import os
import json

class template_replacement:
    key: str
    replacement: str

    def __init__( self, tmpl_key: str, tmpl_replacement: str ):
        self.key = tmpl_key
        self.replacement = tmpl_replacement
    
    def get_key_str( self ):
        return str(f"{{{self.key}}}") # {key}
    
    def get_replacement_str( self ):
        return str(self.replacement)


# Opens a template file, replaces any keys by loading the json, then writes the output to a new file
# This needs to be run from Flight-Computer-Firmware/
def replace_from_template( template_path: str, filepath: str ):
    dir = os.getcwd() + "/"
    json_path = dir + "test/tools/templates/generator_config.json"

    config_data = get_json_data(json_path)

    replacers = []
    for entry in config_data["key_pairs"]:
        key, replacement = entry
        pair = template_replacement(key, replacement)
        replacers.append(pair)

    template_file: str
    with open(dir + template_path, 'r') as tmpl:
        template_file = tmpl.read()
        for replacer in replacers:
            tmp = template_file.replace( replacer.get_key_str(), replacer.get_replacement_str() ) 
            template_file = tmp

    with open(dir + filepath, 'w') as out:
        out.write(template_file)


# Does the same thing as replace_from_template but 
# Overwrites the file!
def replace_in_file( filepath: str ):
    replace_from_template( filepath, filepath )


# The stub needs to include the newlines
# otherwise big evil unreadable block of text
def make_function_stubs( names: list[str] ) -> str:
    dir = os.getcwd()
    json_path = dir + "test/tools/templates/generator_config.json"

    config = get_json_data(json_path)

    # This stub is modifable, but looks like this by default:
    # void test_case_{}()
    #     {
    #     TEST_assert_eq( "STUB: Test not written", FALSE );
    #     }/n
    stub = config["function_stub"]

    text_block = ""
    for name in names:
        text_block += stub.format(name)


def get_json_data( filepath: str ) -> dict:
    with open(filepath, 'r') as config:
        config_data = json.load(config)
        return config_data


def main():
    raise "This file does nothing on its own"


if __name__ == "__main__":
    main()
