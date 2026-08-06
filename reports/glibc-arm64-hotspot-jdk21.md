---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786020954 53
1786020959 53
1786020964 53
1786020969 53
1786020974 53
1786020979 53
1786020984 53
1786020989 53
1786020994 53
1786020999 53
1786021004 53
1786021009 53
1786021014 53
1786021019 53
1786021024 53
1786021029 48
1786021034 48
1786021039 48
1786021044 48
1786021049 48
```
</details>

---

