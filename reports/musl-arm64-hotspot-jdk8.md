---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-24 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 49-56 cores)</summary>

```
1792835494 55
1792835499 55
1792835504 55
1792835509 56
1792835514 56
1792835519 56
1792835524 56
1792835529 56
1792835534 56
1792835539 56
1792835544 56
1792835549 56
1792835554 56
1792835559 56
1792835564 49
1792835569 49
1792835574 49
1792835579 49
1792835584 49
1792835589 49
```
</details>

---

