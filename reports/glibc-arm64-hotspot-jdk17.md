---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:29:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 13-15 cores)</summary>

```
1789712754 13
1789712759 15
1789712764 15
1789712769 15
1789712774 15
1789712779 15
1789712784 15
1789712789 15
1789712794 15
1789712799 15
1789712804 15
1789712809 15
1789712814 15
1789712819 15
1789712824 15
1789712829 15
1789712834 15
1789712839 15
1789712844 15
1789712849 15
```
</details>

---

