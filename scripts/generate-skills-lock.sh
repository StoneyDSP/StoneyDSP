#!/bin/sh

set -eu

root_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
output_path="$root_dir/skills-lock.json"
check_mode=0

if [ "${1:-}" = "--check" ]; then
    check_mode=1
fi

hash_file() {
    if command -v shasum >/dev/null 2>&1; then
        shasum -a 256 "$1" | awk '{print $1}'
    else
        sha256sum "$1" | awk '{print $1}'
    fi
}

skill_paths=$(find "$root_dir/.agents/skills" -type f -name SKILL.md | sort)
skills_json=''

for skill_path in $skill_paths; do
    relative_path=${skill_path#"$root_dir/"}
    name=$(awk -F': ' '$1 == "name" { print $2; exit }' "$skill_path")
    description=$(awk -F': ' '$1 == "description" { print substr($0, index($0, ": ") + 2); exit }' "$skill_path")
    hash=$(hash_file "$skill_path")

    entry=$(printf '    {\n      "name": "%s",\n      "description": "%s",\n      "path": "%s",\n      "sha256": "%s"\n    }' "$name" "$description" "$relative_path" "$hash")

    if [ -n "$skills_json" ]; then
        skills_json="$skills_json,\n$entry"
    else
        skills_json="$entry"
    fi
done

generated=$(mktemp "${TMPDIR:-/tmp}/stoneydsp-skills-lock.XXXXXX")
trap 'rm -f "$generated"' EXIT HUP INT TERM

{
    printf '{\n'
    printf '  "schemaVersion": 1,\n'
    printf '  "generatedFrom": ".agents/skills/**/SKILL.md",\n'
    printf '  "skills": [\n'
    printf '%b\n' "$skills_json"
    printf '  ]\n'
    printf '}\n'
} > "$generated"

if [ "$check_mode" -eq 1 ]; then
    if ! cmp -s "$generated" "$output_path"; then
        echo "skills-lock.json is stale. Run make skills-lock." >&2
        exit 1
    fi
else
    cp "$generated" "$output_path"
fi
