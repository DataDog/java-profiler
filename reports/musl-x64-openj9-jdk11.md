---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 83-91 cores)</summary>

```
1794930695 83
1794930700 83
1794930705 83
1794930710 83
1794930715 83
1794930720 85
1794930725 85
1794930730 87
1794930735 87
1794930740 87
1794930745 83
1794930750 83
1794930755 83
1794930760 83
1794930765 83
1794930770 83
1794930775 83
1794930780 83
1794930785 83
1794930790 85
```
</details>

---

