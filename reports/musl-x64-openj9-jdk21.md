---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 53-75 cores)</summary>

```
1794567536 53
1794567541 53
1794567546 73
1794567551 73
1794567556 71
1794567561 71
1794567566 71
1794567571 71
1794567576 71
1794567581 71
1794567586 71
1794567591 71
1794567596 75
1794567601 75
1794567606 75
1794567611 75
1794567616 75
1794567621 75
1794567626 75
1794567631 75
```
</details>

---

