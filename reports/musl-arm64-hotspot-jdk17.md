---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 08:59:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (4 unique values: 17-24 cores)</summary>

```
1786020954 17
1786020959 17
1786020964 17
1786020969 17
1786020974 20
1786020979 20
1786020984 22
1786020989 22
1786020994 22
1786020999 22
1786021004 22
1786021009 22
1786021014 22
1786021019 22
1786021024 22
1786021029 22
1786021034 22
1786021039 22
1786021044 22
1786021049 22
```
</details>

---

