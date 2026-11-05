---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 07:14:28 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1793880492 45
1793880497 45
1793880502 45
1793880507 45
1793880512 45
1793880517 45
1793880522 45
1793880527 45
1793880532 45
1793880537 45
1793880542 45
1793880547 45
1793880552 45
1793880557 45
1793880562 45
1793880567 45
1793880572 45
1793880577 43
1793880582 43
1793880587 43
```
</details>

---

