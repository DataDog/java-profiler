---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:16:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 56-64 cores)</summary>

```
1790604690 62
1790604695 62
1790604700 64
1790604705 64
1790604710 64
1790604715 64
1790604720 64
1790604725 64
1790604730 64
1790604735 64
1790604740 64
1790604745 64
1790604750 64
1790604755 64
1790604760 64
1790604765 64
1790604770 64
1790604775 64
1790604780 56
1790604785 56
```
</details>

---

