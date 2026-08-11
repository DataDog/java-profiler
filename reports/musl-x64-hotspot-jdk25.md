---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 11:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 83-92 cores)</summary>

```
1786462942 84
1786462947 84
1786462952 84
1786462957 85
1786462962 85
1786462967 85
1786462972 85
1786462977 83
1786462982 83
1786462987 83
1786462992 85
1786462997 85
1786463002 90
1786463007 90
1786463012 90
1786463017 90
1786463022 90
1786463027 90
1786463032 92
1786463037 92
```
</details>

---

