---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 05:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1787046261 86
1787046266 86
1787046271 86
1787046276 86
1787046281 94
1787046286 94
1787046291 94
1787046296 96
1787046301 96
1787046306 96
1787046311 96
1787046316 96
1787046321 96
1787046326 96
1787046331 96
1787046336 96
1787046341 96
1787046346 96
1787046351 96
1787046356 96
```
</details>

---

