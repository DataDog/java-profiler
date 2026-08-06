---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 08:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1786020956 56
1786020961 56
1786020966 56
1786020971 56
1786020976 56
1786020981 56
1786020986 56
1786020991 56
1786020996 56
1786021002 56
1786021007 56
1786021012 56
1786021017 56
1786021022 51
1786021027 51
1786021032 51
1786021037 51
1786021042 51
1786021047 51
1786021052 51
```
</details>

---

