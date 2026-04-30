---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:12:28 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (7 unique values: 53-77 cores)</summary>

```
1777558058 55
1777558063 55
1777558068 53
1777558073 53
1777558078 53
1777558083 59
1777558088 59
1777558093 64
1777558098 64
1777558103 68
1777558108 68
1777558113 68
1777558118 73
1777558123 73
1777558128 73
1777558133 73
1777558138 73
1777558143 73
1777558148 73
1777558153 73
```
</details>

---

