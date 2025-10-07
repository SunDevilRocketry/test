import os
import json

class TemplateReplacement:
    def __init__(self):
        self.config = {"key_pairs": []}

    def load_json_config(self, config_path: str):
        self.config = self.get_json_data(config_path)

    @staticmethod
    def get_json_data(filepath: str) -> dict:
        with open(filepath, 'r') as config:
            return json.load(config)
    
    @staticmethod
    def _get_key_format(key: str):
        return f"{{{key}}}" # {key}
    
    def get_key_strings(self) -> list[str]:
        return [pair[0] for pair in self.config["key_pairs"]]

    def get_replacement_strings(self) -> list[str]:
        return [pair[1] for pair in self.config["key_pairs"]]

    def add_key_pair(self, pair):
        self.config["key_pairs"].append(list(pair))
    
    # Opens a template file, replaces any keys, then writes the output to a new file
    def replace_from_template(self, template_path: str, filepath: str):
        try:
            replacers = self.config["key_pairs"]
        except KeyError:
            print("Error: No replacement pairs defined")
            return

        template_file: str
        with open(template_path, 'r') as tmpl:
            template_file = tmpl.read()
            for replacer in replacers:
                template_file = template_file.replace(self._get_key_format(replacer[0]), replacer[1]) 

        with open(filepath, 'w') as out:
            out.write(template_file)

    # Does the same thing as replace_from_template but overwrites the file
    def replace_in_file(self, filepath: str):
        self.replace_from_template(filepath, filepath)
    
    def make_function_stubs(self, names: list[str]) -> str:
            # This stub is modifable, but looks like this by default when pasted in:
            # void test_case_{name}()
            #     {
            #     TEST_assert_eq( "STUB: Test not written", FALSE );
            #     }
            #
            stub = self.config.get("function_stub")

            text_block = ""
            if stub is not None:
                for name in names:
                    text_block += stub.format(name)
            else:
                print("Error: No function stub specified")

            return text_block


def main():
    raise SystemExit("Exiting - this script does nothing on its own")


if __name__ == "__main__":
    main()
