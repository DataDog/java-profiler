---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 15:37:56 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 10 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795466008 60
1795466013 60
1795466018 60
1795466023 60
1795466028 62
1795466033 62
1795466038 62
1795466043 62
1795466048 62
1795466053 62
1795466058 62
1795466063 62
1795466068 62
1795466073 62
1795466078 62
1795466083 62
1795466088 62
1795466093 62
1795466098 62
1795466103 62
```
</details>

---

