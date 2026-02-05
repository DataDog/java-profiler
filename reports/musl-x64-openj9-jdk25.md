---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 05:23:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 13 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 82-91 cores)</summary>

```
1770286670 91
1770286675 91
1770286680 91
1770286685 91
1770286690 82
1770286695 82
1770286700 82
1770286705 82
1770286710 82
1770286715 82
1770286720 82
1770286725 82
1770286730 82
1770286735 82
1770286740 82
1770286745 82
1770286750 82
1770286755 82
1770286760 82
1770286765 82
```
</details>

---

