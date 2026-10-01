---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-01 07:23:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-43 cores)</summary>

```
1790853565 36
1790853570 38
1790853575 38
1790853580 38
1790853585 38
1790853590 38
1790853595 38
1790853600 38
1790853605 38
1790853610 38
1790853615 38
1790853620 43
1790853625 43
1790853630 43
1790853635 43
1790853640 43
1790853645 43
1790853650 43
1790853655 43
1790853660 43
```
</details>

---

