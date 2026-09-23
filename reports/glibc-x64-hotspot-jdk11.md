---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:09:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 38-41 cores)</summary>

```
1790168627 38
1790168632 38
1790168637 38
1790168642 38
1790168647 41
1790168652 41
1790168657 41
1790168662 41
1790168667 41
1790168672 41
1790168677 41
1790168682 41
1790168687 41
1790168692 41
1790168697 41
1790168702 41
1790168707 41
1790168712 41
1790168717 41
1790168722 41
```
</details>

---

