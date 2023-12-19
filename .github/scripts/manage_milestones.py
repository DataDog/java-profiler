from github import Github
import argparse
import os

# Parsing command line arguments
parser = argparse.ArgumentParser(description="Manage GitHub Milestones")
parser.add_argument("previous_version", help="Previous version for the milestone")
parser.add_argument("current_version", help="Current version for the milestone")
args = parser.parse_args()

# Initialize GitHub client
g = Github(os.environ['GITHUB_TOKEN'])
repo = g.get_repo(os.environ['GITHUB_REPOSITORY'])

current_version = args.current_version
previous_version = args.previous_version

def get_milestone_by_title(title):
    for milestone in repo.get_milestones():
        if milestone.title == title:
            return milestone
    return None

def create_milestone(title):
    repo.create_milestone(title=title)

def close_milestone(title, milestone):
    milestone.edit(title=title, state="closed")

def assign_prs_to_milestone(milestone):
    prs = repo.get_pulls(state='all')
    for pr in prs:
        if pr.merged and previous_version <= pr.merge_commit_sha < current_version:
            if not pr.milestone:
                pr.edit(title=previous_version, milestone=milestone)

previous_milestone = get_milestone_by_title(previous_version)
if previous_milestone:
    assign_prs_to_milestone(previous_milestone)
    close_milestone(previous_version, previous_milestone)

new_milestone = get_milestone_by_title(current_version)
if not new_milestone:
    create_milestone(current_version)
