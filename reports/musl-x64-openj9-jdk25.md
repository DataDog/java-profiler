---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:44:25 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 85-94 cores)</summary>

```
1795426785 94
1795426790 86
1795426795 86
1795426801 86
1795426806 86
1795426811 86
1795426816 86
1795426821 86
1795426826 86
1795426831 86
1795426836 86
1795426841 86
1795426846 86
1795426851 86
1795426856 86
1795426861 86
1795426866 86
1795426871 88
1795426876 88
1795426881 88
```
</details>

---

