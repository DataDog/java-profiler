---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:14:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (6 unique values: 17-30 cores)</summary>

```
1793880509 17
1793880514 17
1793880519 17
1793880524 17
1793880529 19
1793880534 19
1793880539 19
1793880544 19
1793880549 19
1793880554 19
1793880559 18
1793880564 18
1793880569 18
1793880574 18
1793880579 18
1793880584 18
1793880589 18
1793880594 18
1793880599 21
1793880604 21
```
</details>

---

