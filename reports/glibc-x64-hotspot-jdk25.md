---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 5 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 53-57 cores)</summary>

```
1795706021 57
1795706026 57
1795706031 57
1795706036 53
1795706041 53
1795706046 53
1795706051 53
1795706056 53
1795706061 53
1795706066 53
1795706071 53
1795706076 53
1795706081 53
1795706086 53
1795706091 53
1795706096 53
1795706101 53
1795706106 53
1795706111 53
1795706116 53
```
</details>

---

