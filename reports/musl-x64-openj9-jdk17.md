---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 81-86 cores)</summary>

```
1777558050 81
1777558055 81
1777558060 81
1777558065 81
1777558070 81
1777558075 81
1777558080 81
1777558085 81
1777558090 81
1777558095 81
1777558100 81
1777558105 86
1777558110 86
1777558115 86
1777558120 86
1777558125 86
1777558130 84
1777558135 84
1777558140 86
1777558145 86
```
</details>

---

