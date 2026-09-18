---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:47:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1789731700 48
1789731705 48
1789731710 47
1789731715 47
1789731720 47
1789731725 47
1789731730 47
1789731735 47
1789731740 47
1789731745 46
1789731750 46
1789731755 46
1789731760 46
1789731765 46
1789731770 46
1789731775 46
1789731780 46
1789731785 46
1789731790 46
1789731795 46
```
</details>

---

