---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:06:32 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 15 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1786971665 20
1786971670 32
1786971675 32
1786971680 32
1786971685 32
1786971690 32
1786971695 32
1786971700 32
1786971705 32
1786971710 32
1786971715 32
1786971720 32
1786971725 32
1786971730 32
1786971735 32
1786971740 32
1786971745 32
1786971750 32
1786971755 32
1786971760 32
```
</details>

---

