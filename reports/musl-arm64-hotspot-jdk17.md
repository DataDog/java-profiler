---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:28:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1790241544 43
1790241549 43
1790241554 43
1790241559 43
1790241564 43
1790241569 43
1790241574 43
1790241579 43
1790241584 43
1790241589 43
1790241594 43
1790241599 43
1790241604 43
1790241609 42
1790241614 42
1790241619 42
1790241624 42
1790241629 42
1790241634 42
1790241639 42
```
</details>

---

