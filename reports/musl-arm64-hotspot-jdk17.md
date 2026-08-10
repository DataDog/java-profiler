---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:47:04 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 10 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 17-64 cores)</summary>

```
1786358575 17
1786358580 17
1786358585 17
1786358590 17
1786358595 17
1786358600 17
1786358605 17
1786358610 17
1786358615 17
1786358620 17
1786358625 17
1786358630 17
1786358635 17
1786358640 17
1786358645 17
1786358650 64
1786358655 64
1786358660 64
1786358665 64
1786358670 64
```
</details>

---

