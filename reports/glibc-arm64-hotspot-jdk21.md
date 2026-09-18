---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:15:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 29 |
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
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1789743655 23
1789743660 23
1789743665 23
1789743670 23
1789743675 33
1789743680 33
1789743685 33
1789743690 23
1789743695 23
1789743700 23
1789743705 23
1789743710 29
1789743715 29
1789743720 29
1789743725 29
1789743730 29
1789743735 29
1789743740 29
1789743745 29
1789743750 29
```
</details>

---

