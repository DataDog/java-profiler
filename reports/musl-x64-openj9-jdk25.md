---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:53:39 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (6 unique values: 44-54 cores)</summary>

```
1795106927 51
1795106932 51
1795106937 51
1795106942 51
1795106948 51
1795106953 51
1795106958 51
1795106963 53
1795106968 53
1795106973 44
1795106978 44
1795106983 46
1795106988 46
1795106993 50
1795106998 50
1795107003 50
1795107008 50
1795107013 50
1795107018 54
1795107023 54
```
</details>

---

