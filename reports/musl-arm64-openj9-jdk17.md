---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 08:09:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1795525398 21
1795525403 21
1795525408 21
1795525413 16
1795525418 16
1795525423 16
1795525428 16
1795525433 16
1795525438 16
1795525443 16
1795525448 16
1795525453 16
1795525458 16
1795525463 16
1795525468 16
1795525473 16
1795525478 16
1795525483 16
1795525488 16
1795525493 21
```
</details>

---

