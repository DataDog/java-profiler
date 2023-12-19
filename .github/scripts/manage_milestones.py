from github import Github
import argparse
import os

# Parsing command line arguments
parser = argparse.ArgumentParser(description="Manage GitHub Milestones")
parser.add_argume("action", help="Action to perform on the milestone", choices=["create", "close", "assign", "release"])
parser.add_argument("version", help="Version for the milestone")
parser.add_argument("previous_version", optional=True, help="Previous version for the milestone. Only for 'release' action")
args = parser.parse_args()

# Initialize GitHub client
g = Github(os.environ['GITHUB_TOKEN'])
repo = g.get_repo(os.environ['GITHUB_REPOSITORY'])

action = args.action
version = args.version
previous_version = args.previous_version

def get_milestone_by_title(title):
    for milestone in repo.get_milestones():
        if milestone.title == title:
            return milestone
    return None

def create_milestone(title):
    new_milestone = get_milestone_by_title(title)
    if not new_milestone:
        repo.create_milestone(title=title)

def close_milestone(title):
    milestone = get_milestone_by_title(title)
    if milestone:
        milestone.edit(title=title, state="closed")

def assign_prs_to_milestone(title):
    milestone = get_milestone_by_title(title)
    if milestone:
        prs = repo.get_pulls(state='all')
        for pr in prs:
            if pr.merged and version <= pr.merge_commit_sha:
                if not pr.milestone:
                    pr.edit(title=version, milestone=milestone)

if action == "create":
    create_milestone(version)
elif action == "close":
    close_milestone(version)
elif action == "assign":
    assign_prs_to_milestone(version)
elif action == "release":
    create_milestone(version)
    close_milestone(previous_version)
    assign_prs_to_milestone(version)
else:
    print("Invalid action:", action)
    exit(1)