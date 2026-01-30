---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-30 04:28:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 24.27/sec |
| Health Score | 1517% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 26-32 cores)</summary>

```
1769764882 32
1769764887 32
1769764892 32
1769764897 32
1769764902 32
1769764907 32
1769764912 32
1769764917 32
1769764922 32
1769764927 32
1769764932 32
1769764937 32
1769764942 32
1769764947 32
1769764952 32
1769764957 32
1769764962 32
1769764967 32
1769764972 32
1769764977 32
```
</details>

---

