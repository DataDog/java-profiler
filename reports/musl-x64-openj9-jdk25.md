---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:15:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 56-76 cores)</summary>

```
1794352212 76
1794352217 76
1794352222 76
1794352227 76
1794352232 76
1794352237 56
1794352242 56
1794352247 56
1794352252 56
1794352257 56
1794352262 56
1794352267 56
1794352272 56
1794352277 56
1794352282 56
1794352287 56
1794352292 56
1794352297 56
1794352302 56
1794352307 56
```
</details>

---

