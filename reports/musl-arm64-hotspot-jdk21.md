---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 04:54:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 7 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1794390401 54
1794390406 54
1794390411 59
1794390416 59
1794390421 59
1794390426 59
1794390431 59
1794390436 59
1794390441 59
1794390446 59
1794390451 59
1794390456 59
1794390461 59
1794390466 59
1794390471 59
1794390476 59
1794390481 59
1794390486 59
1794390491 59
1794390496 59
```
</details>

---

