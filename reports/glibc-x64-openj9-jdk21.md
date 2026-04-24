---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:31:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 20-21 cores)</summary>

```
1777033695 21
1777033700 21
1777033705 21
1777033710 21
1777033715 21
1777033720 21
1777033725 21
1777033730 21
1777033735 21
1777033740 21
1777033745 21
1777033750 21
1777033755 21
1777033760 21
1777033765 21
1777033770 21
1777033775 20
1777033780 20
1777033785 20
1777033790 20
```
</details>

---

