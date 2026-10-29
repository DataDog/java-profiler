---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:19:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793293979 32
1793293984 32
1793293989 32
1793293994 32
1793293999 32
1793294004 32
1793294009 32
1793294014 32
1793294019 32
1793294024 32
1793294029 32
1793294034 32
1793294039 32
1793294044 32
1793294049 32
1793294054 32
1793294059 32
1793294064 32
1793294069 32
1793294074 32
```
</details>

---

