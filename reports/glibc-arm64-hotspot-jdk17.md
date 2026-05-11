---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 19:24:12 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1778541640 60
1778541645 60
1778541650 60
1778541655 60
1778541660 60
1778541665 60
1778541670 60
1778541675 60
1778541680 60
1778541685 60
1778541690 60
1778541695 60
1778541700 60
1778541705 60
1778541710 60
1778541715 60
1778541720 60
1778541725 60
1778541730 60
1778541735 60
```
</details>

---

