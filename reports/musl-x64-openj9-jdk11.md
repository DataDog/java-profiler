---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:20:06 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1795014924 83
1795014929 83
1795014934 83
1795014939 83
1795014944 83
1795014949 83
1795014954 83
1795014959 83
1795014964 83
1795014969 83
1795014974 83
1795014979 81
1795014984 81
1795014989 81
1795014994 81
1795014999 81
1795015004 83
1795015009 83
1795015014 83
1795015019 83
```
</details>

---

