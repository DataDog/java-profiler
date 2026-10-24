---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-24 05:55:19 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 33-72 cores)</summary>

```
1792835490 72
1792835495 72
1792835500 72
1792835505 72
1792835510 72
1792835515 37
1792835520 37
1792835525 37
1792835530 37
1792835535 37
1792835540 37
1792835545 39
1792835550 39
1792835555 39
1792835560 39
1792835565 33
1792835570 33
1792835575 33
1792835580 33
1792835585 35
```
</details>

---

