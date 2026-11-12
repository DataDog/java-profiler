---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:53:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (5 unique values: 66-81 cores)</summary>

```
1794498354 66
1794498359 66
1794498364 66
1794498369 66
1794498374 66
1794498379 66
1794498384 68
1794498389 68
1794498394 68
1794498399 68
1794498404 68
1794498409 77
1794498414 77
1794498419 77
1794498424 77
1794498429 77
1794498434 79
1794498439 79
1794498444 79
1794498449 79
```
</details>

---

