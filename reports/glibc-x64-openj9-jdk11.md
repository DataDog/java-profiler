---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 30-68 cores)</summary>

```
1795803655 59
1795803660 59
1795803665 59
1795803670 59
1795803675 59
1795803680 68
1795803685 68
1795803690 58
1795803695 58
1795803700 58
1795803705 58
1795803710 58
1795803715 58
1795803720 58
1795803725 58
1795803730 68
1795803735 68
1795803740 40
1795803745 40
1795803750 50
```
</details>

---

