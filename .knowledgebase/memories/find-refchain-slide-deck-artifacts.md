---
id: find-refchain-slide-deck-artifacts
title: 6-slide reference-chain deck authored as hand-laid-out SVG (mermaid rejected for layout quality)
kind: finding
tags: [java-profiler, reference-chains, slides, artifacts]
applies_to: []
source: user-invoked-sphinx-arguments/find-refchain-slide-deck-artifacts
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# 6-slide reference-chain deck authored as hand-laid-out SVG (mermaid rejected for layout quality)

## Reasoning chain
User wanted Google-Slides-embeddable diagrams for reference-chain collection.
Mermaid auto-layout produced unusable aspect ratios and typography; final deck is
hand-authored SVG on a 1920×1080 grid (80px margins, single type scale, 5-color
semantic palette, orthogonal arrows), rendered via rsvg-convert. Slides: 1 overview,
2 triggers/gates, 3 pass anatomy, 4 per-pass pacing guardrails, 5 cutoffs+OOM urgency,
6 output/JFR consistency. Titles were deliberately dropped (user adds them in Slides);
backgrounds transparent; canvas cropped to content (per-slide aspect ~2.1-2.7:1).
s6 header corrected from "at dump time" to "each pass, on the engine thread" after
user challenged it — reconstruction is per-pass, dump is emission only.

## Evidence
- build/slides/reference-chains/{svg/*.svg, slide16x9/*.png} in the
  java-profiler-rc-6-java-tests worktree (build/, not committed)
- Regenerate: rsvg-convert svg/x.svg -o slide16x9/x.png (omit -b white for transparency)
