---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-30 04:28:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 24.03/sec |
| Health Score | 1502% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 21-26 cores)</summary>

```
1769764882 24
1769764887 24
1769764892 22
1769764897 22
1769764902 22
1769764907 22
1769764912 24
1769764917 24
1769764922 24
1769764927 24
1769764932 24
1769764937 24
1769764942 24
1769764947 24
1769764952 26
1769764957 26
1769764962 26
1769764967 26
1769764972 26
1769764977 26
```
</details>

---

