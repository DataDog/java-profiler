---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-08 20:29:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 8-13 cores)</summary>

```
1794187476 8
1794187481 8
1794187486 8
1794187491 8
1794187496 8
1794187501 8
1794187506 8
1794187511 8
1794187516 8
1794187521 8
1794187526 8
1794187531 8
1794187536 8
1794187541 13
1794187546 13
1794187551 8
1794187556 8
1794187561 8
1794187566 8
1794187571 8
```
</details>

---

