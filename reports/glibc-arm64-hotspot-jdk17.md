---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 08:32:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 34-48 cores)</summary>

```
1791980533 48
1791980539 39
1791980544 39
1791980549 39
1791980554 39
1791980559 39
1791980564 39
1791980569 39
1791980574 39
1791980579 39
1791980584 39
1791980589 39
1791980594 39
1791980599 34
1791980604 34
1791980609 34
1791980614 34
1791980619 34
1791980624 34
1791980629 34
```
</details>

---

