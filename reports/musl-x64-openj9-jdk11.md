---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:55:35 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794945031 30
1794945036 30
1794945041 30
1794945046 30
1794945051 30
1794945056 30
1794945061 30
1794945066 32
1794945071 32
1794945076 32
1794945081 32
1794945086 32
1794945091 32
1794945096 32
1794945101 32
1794945106 32
1794945111 32
1794945116 32
1794945121 32
1794945126 32
```
</details>

---

