# Copyright 2026, Datadog, Inc.
"""Exercise the certification subject and its release-time verifier without network access."""

import json
import os
from pathlib import Path
import subprocess
import tempfile
import textwrap
import unittest

from test_certification_workflow import ROOT, job


VERIFY = ROOT / '.github/scripts/verify-release-certification.sh'
WORKFLOWS = ROOT / '.github/workflows'
SHA = '1234567890abcdef' * 2 + '76543210'


class ReleaseCertificationTest(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.work = Path(temp.name)
        gh = self.work / 'gh'
        gh.write_text('''#!/usr/bin/env python3
import json, os, pathlib, sys
args = sys.argv[1:]
path = pathlib.Path(args[2])
pathlib.Path(os.environ['CAPTURE']).write_text(json.dumps([args, path.read_text()]))
sys.exit(int(os.environ.get('GH_EXIT', 0)))
''')
        gh.chmod(0o700)
        self.capture = self.work / 'capture.json'
        self.env = dict(os.environ, PATH=str(self.work) + os.pathsep + os.environ['PATH'],
                        CAPTURE=str(self.capture), TMPDIR=str(self.work))

    def verify(self, *args, gh_exit=0):
        return subprocess.run(['bash', str(VERIFY), *args], cwd=self.work,
                              env=dict(self.env, GH_EXIT=str(gh_exit)), capture_output=True, text=True)

    def test_signer_and_verifier_agree_on_exact_bytes_and_identity(self):
        certify = job((WORKFLOWS / 'certification.yml').read_text(), 'certify')
        write = certify.split('id: subject\n', 1)[1].split('run: |\n', 1)[1].split('      - name:', 1)[0]
        output = self.work / 'output'
        subprocess.run(['bash', '-ec', textwrap.dedent(write)], check=True,
                       env=dict(self.env, GITHUB_SHA=SHA, GITHUB_OUTPUT=str(output)))
        path = Path(output.read_text().strip().removeprefix('path='))
        self.assertEqual(path.name, 'certified-commit.txt')
        self.assertEqual(path.read_bytes(), (SHA + '\n').encode())
        self.assertIn('subject-path: ${{ steps.subject.outputs.path }}', certify)
        self.assertLess(certify.index('uses: actions/attest@'), certify.index('.github/scripts/certify.sh'))
        result = self.verify(SHA)
        self.assertEqual(result.returncode, 0, result.stderr)
        args, body = json.loads(self.capture.read_text())
        self.assertEqual(args[:2], ['attestation', 'verify'])
        self.assertEqual(body.encode(), path.read_bytes())
        self.assertEqual(Path(args[2]).name, path.name)
        self.assertEqual(args[3:], ['--repo', 'DataDog/java-profiler', '--signer-workflow',
                                    'DataDog/java-profiler/.github/workflows/certification.yml',
                                    '--source-ref', 'refs/heads/main', '--source-digest', SHA,
                                    '--deny-self-hosted-runners'])

    def test_verification_failure_blocks_without_note_fallback(self):
        self.assertEqual(self.verify(SHA, gh_exit=7).returncode, 7)
        self.assertFalse(Path(json.loads(self.capture.read_text())[0][2]).exists())

    def test_invalid_candidate_never_invokes_verifier(self):
        for args in ((), ('main',), (SHA[:-1],), (SHA + 'a',), ('g' * 40,), (SHA, SHA)):
            with self.subTest(args=args):
                self.assertEqual(self.verify(*args).returncode, 2)
                self.assertFalse(self.capture.exists())

    def test_both_release_entry_points_verify_the_resolved_sha(self):
        train = job((WORKFLOWS / 'release-train.yml').read_text(), 'release')
        check = train.index('bash .github/scripts/verify-release-certification.sh "$CANDIDATE"')
        self.assertLess(train.index('CANDIDATE="$OUT"'), check)
        self.assertLess(train.index('CANDIDATE=$(git rev-parse'), check)
        self.assertLess(check, train.index('echo "candidate=$CANDIDATE"'))
        release = (WORKFLOWS / 'release-validated.yml').read_text()
        inputs = job(release, 'validate-inputs')
        self.assertIn('$GITHUB_REF_TYPE != branch || $GITHUB_REF_PROTECTED != true', inputs)
        self.assertIn('[ "$GITHUB_REF" != refs/heads/main ]', inputs)
        writer = job(release, 'create-release')
        check = writer.split('- name: Verify mainline release certification', 1)[1].split('- name:', 1)[0]
        self.assertIn("if: inputs.release_type == 'major' || inputs.release_type == 'minor'", check)
        self.assertNotIn('skip_tests', check)
        self.assertIn('TARGET_SHA: ${{ needs.validate-inputs.outputs.target_sha }}', check)
        self.assertIn('bash .github/scripts/verify-release-certification.sh "$TARGET_SHA"', check)
        self.assertLess(writer.index(check), writer.index('secrets.RELEASE_ENV_PUSH_KEY'))
        self.assertNotIn('SSH_PUSH_SECRET', writer)
        self.assertIn("(inputs.release_type == 'patch' || inputs.release_type == 'retag') && "
                      "'release-maintenance' || 'release-mainline'", writer)


if __name__ == '__main__':
    unittest.main()
