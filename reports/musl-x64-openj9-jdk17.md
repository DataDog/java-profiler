---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-12 10:57:36 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1794498725 80
1794498730 80
1794498735 80
1794498740 80
1794498745 80
1794498750 80
1794498755 80
1794498760 78
1794498765 78
1794498771 78
1794498776 78
1794498781 78
1794498786 82
1794498791 82
1794498796 82
1794498801 84
1794498806 84
1794498811 84
1794498816 84
1794498821 84
```
</details>

---

