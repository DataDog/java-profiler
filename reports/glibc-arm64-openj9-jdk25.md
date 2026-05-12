---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 09:20:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 14 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 52-57 cores)</summary>

```
1778591616 57
1778591621 57
1778591626 57
1778591631 57
1778591636 52
1778591641 52
1778591646 52
1778591651 52
1778591656 52
1778591661 52
1778591666 52
1778591671 52
1778591676 52
1778591681 52
1778591686 52
1778591691 52
1778591696 52
1778591701 52
1778591706 52
1778591711 52
```
</details>

---

