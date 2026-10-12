---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 09:14:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 11 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791810606 43
1791810611 48
1791810616 48
1791810621 48
1791810626 48
1791810631 48
1791810636 48
1791810641 48
1791810646 48
1791810651 48
1791810656 48
1791810661 48
1791810666 48
1791810671 48
1791810676 48
1791810681 48
1791810686 48
1791810691 48
1791810696 48
1791810701 48
```
</details>

---

