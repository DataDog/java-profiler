---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795706005 44
1795706010 44
1795706015 44
1795706020 44
1795706026 44
1795706031 44
1795706036 64
1795706041 64
1795706046 64
1795706051 64
1795706056 64
1795706061 64
1795706066 64
1795706071 64
1795706076 64
1795706081 64
1795706086 64
1795706091 64
1795706096 64
1795706101 64
```
</details>

---

