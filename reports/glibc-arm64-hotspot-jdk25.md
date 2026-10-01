---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:23:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 31-43 cores)</summary>

```
1790853590 31
1790853595 31
1790853600 31
1790853605 31
1790853610 31
1790853615 31
1790853620 31
1790853625 31
1790853630 31
1790853635 31
1790853640 43
1790853645 43
1790853650 43
1790853655 43
1790853660 43
1790853665 43
1790853670 43
1790853675 43
1790853680 43
1790853685 43
```
</details>

---

