---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 37 |
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
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (5 unique values: 36-44 cores)</summary>

```
1791546665 44
1791546670 44
1791546675 44
1791546680 44
1791546685 44
1791546690 44
1791546695 44
1791546700 44
1791546705 44
1791546710 44
1791546715 44
1791546720 44
1791546725 43
1791546730 43
1791546735 43
1791546740 43
1791546745 41
1791546750 41
1791546755 41
1791546760 41
```
</details>

---

