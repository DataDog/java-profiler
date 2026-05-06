---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 19:44:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 55-63 cores)</summary>

```
1778110785 55
1778110790 55
1778110795 55
1778110800 55
1778110805 55
1778110810 55
1778110815 55
1778110820 55
1778110825 55
1778110830 55
1778110835 55
1778110840 55
1778110845 55
1778110850 55
1778110855 61
1778110860 61
1778110865 61
1778110870 61
1778110875 61
1778110880 63
```
</details>

---

