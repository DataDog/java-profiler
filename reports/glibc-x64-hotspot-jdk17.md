---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:29:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 58-73 cores)</summary>

```
1795001005 73
1795001010 73
1795001015 73
1795001020 71
1795001025 71
1795001030 71
1795001035 71
1795001040 71
1795001045 71
1795001050 71
1795001055 71
1795001060 73
1795001065 73
1795001070 69
1795001075 69
1795001080 69
1795001085 69
1795001090 69
1795001095 69
1795001100 69
```
</details>

---

