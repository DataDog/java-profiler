---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:39 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1794917987 55
1794917992 55
1794917997 57
1794918002 57
1794918007 57
1794918012 57
1794918017 57
1794918022 57
1794918027 57
1794918033 57
1794918038 57
1794918043 57
1794918048 57
1794918053 57
1794918058 57
1794918063 57
1794918068 57
1794918073 57
1794918078 57
1794918083 57
```
</details>

---

