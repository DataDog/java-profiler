---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 14:55:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 11 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (3 unique values: 33-51 cores)</summary>

```
1794945030 38
1794945035 38
1794945040 38
1794945045 38
1794945050 38
1794945056 38
1794945061 38
1794945066 38
1794945071 38
1794945076 38
1794945081 38
1794945086 38
1794945091 38
1794945096 38
1794945101 38
1794945106 38
1794945111 38
1794945116 51
1794945121 51
1794945126 51
```
</details>

---

