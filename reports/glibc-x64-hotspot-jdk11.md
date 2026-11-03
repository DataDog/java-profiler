---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:45:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1174 |
| Sample Rate | 19.57/sec |
| Health Score | 1223% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 50-59 cores)</summary>

```
1793742036 58
1793742041 58
1793742046 58
1793742051 58
1793742056 58
1793742061 58
1793742066 58
1793742071 58
1793742076 58
1793742081 58
1793742086 58
1793742091 59
1793742096 59
1793742101 59
1793742106 59
1793742111 59
1793742116 59
1793742122 59
1793742127 59
1793742132 59
```
</details>

---

