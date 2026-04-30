---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:12:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 61-71 cores)</summary>

```
1777558045 63
1777558050 63
1777558055 64
1777558060 64
1777558065 64
1777558070 61
1777558075 61
1777558080 63
1777558085 63
1777558090 63
1777558095 63
1777558100 63
1777558105 71
1777558110 71
1777558115 71
1777558120 71
1777558125 71
1777558130 71
1777558135 71
1777558140 69
```
</details>

---

