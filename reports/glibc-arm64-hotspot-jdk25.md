---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 07:06:58 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791543757 48
1791543762 48
1791543767 48
1791543772 48
1791543777 48
1791543782 48
1791543787 48
1791543792 43
1791543797 43
1791543802 43
1791543807 43
1791543812 43
1791543817 43
1791543822 43
1791543827 43
1791543832 43
1791543837 43
1791543842 43
1791543847 43
1791543852 43
```
</details>

---

