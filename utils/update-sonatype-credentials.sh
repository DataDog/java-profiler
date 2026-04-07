#!/bin/bash
set -euo pipefail

# Update Sonatype (Maven Central) credentials in AWS SSM for java-profiler CI.
#
# Usage: update-sonatype-credentials.sh <username> <token>

AWS_REGION=us-east-1
SSM_PREFIX=ci.java-profiler
AWS_VAULT_PROFILE=sso-build-stable-developer

usage() {
  echo "Usage: $0 <username> <token>"
  echo ""
  echo "Updates Sonatype OSSRH credentials in AWS SSM:"
  echo "  ${SSM_PREFIX}.sonatype_token_user"
  echo "  ${SSM_PREFIX}.sonatype_token"
  exit 1
}

if [ $# -ne 2 ]; then
  usage
fi

USERNAME="$1"
TOKEN="$2"

aws-vault login sso-build-stable-developer

# Verify AWS authentication
if ! aws-vault exec "${AWS_VAULT_PROFILE}" -- aws sts get-caller-identity --query "Arn" --output text 2>/dev/null; then
  echo "ERROR: Not authenticated with AWS. Run 'aws-vault login ${AWS_VAULT_PROFILE}' and retry."
  exit 1
fi

echo "Updating ${SSM_PREFIX}.sonatype_token_user ..."
aws-vault exec "${AWS_VAULT_PROFILE}" -- aws ssm put-parameter \
  --region "${AWS_REGION}" \
  --name "${SSM_PREFIX}.sonatype_token_user" \
  --value "${USERNAME}" \
  --type SecureString \
  --overwrite

echo "Updating ${SSM_PREFIX}.sonatype_token ..."
aws-vault exec "${AWS_VAULT_PROFILE}" -- aws ssm put-parameter \
  --region "${AWS_REGION}" \
  --name "${SSM_PREFIX}.sonatype_token" \
  --value "${TOKEN}" \
  --type SecureString \
  --overwrite

echo "Done."
