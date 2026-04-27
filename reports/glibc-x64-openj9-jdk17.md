---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 05:15:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1003 |
| Sample Rate | 16.72/sec |
| Health Score | 1045% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 46-63 cores)</summary>

```
1777281000 63
1777281005 63
1777281010 63
1777281015 63
1777281020 63
1777281025 46
1777281030 46
1777281035 46
1777281040 46
1777281045 46
1777281050 46
1777281055 46
1777281060 46
1777281065 46
1777281070 55
1777281075 55
1777281080 55
1777281085 55
1777281090 55
1777281095 55
```
</details>

---

