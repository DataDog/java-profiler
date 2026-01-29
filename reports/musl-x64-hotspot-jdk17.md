---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 07:01:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 23.97/sec |
| Health Score | 1498% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 67-82 cores)</summary>

```
1769687514 82
1769687519 82
1769687524 82
1769687529 82
1769687534 82
1769687539 82
1769687544 82
1769687549 82
1769687554 82
1769687559 82
1769687564 82
1769687569 77
1769687574 77
1769687579 77
1769687584 77
1769687589 77
1769687594 77
1769687599 77
1769687604 77
1769687609 77
```
</details>

---

