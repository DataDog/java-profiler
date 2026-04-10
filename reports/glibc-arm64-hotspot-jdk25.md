---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-10 14:16:23 EDT

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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775844590 64
1775844595 64
1775844600 64
1775844605 64
1775844610 64
1775844615 64
1775844620 64
1775844625 64
1775844630 64
1775844635 64
1775844640 64
1775844645 64
1775844650 64
1775844655 64
1775844660 64
1775844665 64
1775844671 64
1775844676 64
1775844681 64
1775844686 64
```
</details>

---

