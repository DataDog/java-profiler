---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 73-76 cores)</summary>

```
1795010809 76
1795010814 76
1795010819 76
1795010824 76
1795010829 76
1795010834 76
1795010839 76
1795010844 76
1795010849 76
1795010854 76
1795010859 76
1795010864 76
1795010869 76
1795010874 76
1795010879 76
1795010884 76
1795010889 76
1795010894 76
1795010899 73
1795010904 73
```
</details>

---

