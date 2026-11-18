---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:20:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 9 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795014973 38
1795014978 38
1795014983 38
1795014988 38
1795014993 43
1795014998 43
1795015003 43
1795015008 43
1795015013 43
1795015018 43
1795015023 43
1795015028 43
1795015033 43
1795015038 43
1795015043 43
1795015048 43
1795015053 43
1795015059 43
1795015064 43
1795015069 43
```
</details>

---

