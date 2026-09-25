---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 7 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (3 unique values: 17-59 cores)</summary>

```
1790336050 17
1790336055 17
1790336060 17
1790336065 17
1790336070 17
1790336075 17
1790336080 17
1790336085 17
1790336090 17
1790336095 17
1790336100 17
1790336105 17
1790336110 17
1790336115 54
1790336120 54
1790336125 54
1790336130 54
1790336135 54
1790336140 54
1790336145 59
```
</details>

---

