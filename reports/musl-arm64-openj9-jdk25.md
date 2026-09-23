---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 16:03:19 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 41-50 cores)</summary>

```
1790193533 41
1790193538 41
1790193543 41
1790193548 41
1790193553 41
1790193558 41
1790193563 50
1790193568 50
1790193573 49
1790193578 49
1790193583 49
1790193588 49
1790193593 49
1790193598 49
1790193603 49
1790193608 49
1790193613 49
1790193618 49
1790193623 49
1790193628 50
```
</details>

---

