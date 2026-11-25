---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:01:50 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1795625810 52
1795625815 52
1795625820 52
1795625825 52
1795625830 52
1795625835 52
1795625840 52
1795625845 52
1795625850 54
1795625855 54
1795625860 54
1795625865 54
1795625870 49
1795625875 49
1795625880 49
1795625885 49
1795625890 49
1795625895 49
1795625900 49
1795625905 49
```
</details>

---

