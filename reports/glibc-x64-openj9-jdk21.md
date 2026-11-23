---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:30:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 54-59 cores)</summary>

```
1795397226 56
1795397231 56
1795397236 56
1795397241 56
1795397246 56
1795397251 56
1795397256 56
1795397261 56
1795397266 54
1795397271 54
1795397276 54
1795397281 54
1795397286 54
1795397291 54
1795397296 56
1795397301 56
1795397306 56
1795397311 58
1795397316 58
1795397321 58
```
</details>

---

