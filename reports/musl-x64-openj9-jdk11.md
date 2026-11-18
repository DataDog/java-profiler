---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:30:44 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 19-23 cores)</summary>

```
1795011973 19
1795011978 19
1795011983 19
1795011988 19
1795011993 23
1795011998 23
1795012003 23
1795012008 23
1795012013 23
1795012018 23
1795012023 23
1795012028 23
1795012033 23
1795012038 23
1795012043 23
1795012048 23
1795012053 23
1795012058 23
1795012063 23
1795012068 23
```
</details>

---

