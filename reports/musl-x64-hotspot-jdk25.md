---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 10 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1795529334 80
1795529339 80
1795529344 80
1795529349 82
1795529354 82
1795529359 82
1795529364 84
1795529369 84
1795529374 84
1795529379 84
1795529384 84
1795529389 84
1795529394 84
1795529399 84
1795529404 84
1795529409 84
1795529414 84
1795529419 84
1795529424 82
1795529429 82
```
</details>

---

