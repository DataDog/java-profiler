---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:09:10 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 12 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1786971660 42
1786971665 42
1786971670 47
1786971675 47
1786971680 47
1786971685 47
1786971690 48
1786971695 48
1786971700 48
1786971705 48
1786971710 48
1786971715 48
1786971720 48
1786971725 46
1786971730 46
1786971735 46
1786971740 46
1786971745 46
1786971750 46
1786971755 46
```
</details>

---

