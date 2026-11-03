---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 13:50:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 39-52 cores)</summary>

```
1793731448 39
1793731453 39
1793731458 39
1793731463 39
1793731468 39
1793731473 39
1793731478 39
1793731483 39
1793731488 39
1793731493 39
1793731498 39
1793731503 39
1793731508 39
1793731513 39
1793731518 39
1793731523 39
1793731528 39
1793731533 52
1793731538 52
1793731543 52
```
</details>

---

