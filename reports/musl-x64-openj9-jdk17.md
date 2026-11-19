---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:14:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1795108217 65
1795108222 65
1795108227 65
1795108232 65
1795108237 65
1795108242 65
1795108247 65
1795108252 65
1795108257 65
1795108262 65
1795108267 65
1795108272 65
1795108277 65
1795108282 67
1795108287 67
1795108292 70
1795108297 70
1795108302 72
1795108307 72
1795108312 72
```
</details>

---

