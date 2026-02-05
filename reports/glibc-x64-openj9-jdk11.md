---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-05 05:23:31 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 82-89 cores)</summary>

```
1770286715 84
1770286720 84
1770286725 84
1770286730 84
1770286735 84
1770286740 84
1770286745 84
1770286750 84
1770286755 84
1770286760 84
1770286765 84
1770286770 84
1770286775 84
1770286780 89
1770286785 89
1770286790 89
1770286795 86
1770286800 86
1770286805 86
1770286810 86
```
</details>

---

