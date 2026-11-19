---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:14:20 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1795108232 65
1795108237 65
1795108242 65
1795108247 65
1795108252 65
1795108257 65
1795108262 65
1795108267 65
1795108272 65
1795108277 67
1795108282 67
1795108287 67
1795108292 70
1795108297 70
1795108302 72
1795108307 72
1795108312 72
1795108317 72
1795108322 72
1795108327 72
```
</details>

---

