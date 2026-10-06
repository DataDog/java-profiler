---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1791282922 15
1791282927 15
1791282932 15
1791282937 15
1791282942 15
1791282947 15
1791282952 15
1791282957 15
1791282962 15
1791282967 15
1791282972 15
1791282977 15
1791282982 15
1791282987 15
1791282992 15
1791282997 15
1791283002 15
1791283007 15
1791283012 32
1791283017 32
```
</details>

---

