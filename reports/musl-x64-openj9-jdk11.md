---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:53:38 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795106923 85
1795106928 85
1795106933 85
1795106938 85
1795106943 85
1795106948 85
1795106953 85
1795106958 87
1795106963 87
1795106968 85
1795106973 85
1795106978 85
1795106983 85
1795106988 85
1795106993 85
1795106998 85
1795107003 85
1795107008 85
1795107013 85
1795107018 85
```
</details>

---

