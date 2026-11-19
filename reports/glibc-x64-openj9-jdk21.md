---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:53:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 39-76 cores)</summary>

```
1795106928 76
1795106933 76
1795106938 76
1795106943 76
1795106948 76
1795106953 76
1795106958 76
1795106963 76
1795106968 76
1795106973 76
1795106978 48
1795106983 48
1795106988 48
1795106993 48
1795106998 48
1795107003 48
1795107008 39
1795107013 39
1795107018 39
1795107023 39
```
</details>

---

