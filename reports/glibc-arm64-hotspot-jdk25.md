---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-19 21:19:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 13 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776647612 64
1776647617 64
1776647622 64
1776647627 64
1776647632 64
1776647637 64
1776647642 64
1776647647 64
1776647652 64
1776647657 64
1776647662 64
1776647667 64
1776647672 64
1776647677 64
1776647682 64
1776647687 64
1776647692 64
1776647697 64
1776647702 64
1776647707 64
```
</details>

---

