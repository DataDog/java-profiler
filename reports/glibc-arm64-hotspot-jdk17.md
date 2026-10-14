---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 10:47:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 14 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1791988957 39
1791988962 39
1791988967 39
1791988972 39
1791988977 39
1791988982 39
1791988987 39
1791988992 39
1791988997 39
1791989002 39
1791989007 39
1791989012 44
1791989017 44
1791989022 44
1791989027 44
1791989032 44
1791989037 44
1791989042 44
1791989047 44
1791989052 44
```
</details>

---

