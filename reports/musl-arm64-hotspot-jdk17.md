---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 11:59:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 10 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1787154898 48
1787154903 44
1787154908 44
1787154913 44
1787154918 44
1787154923 44
1787154928 44
1787154933 44
1787154938 44
1787154943 44
1787154948 44
1787154953 44
1787154958 44
1787154963 48
1787154968 48
1787154973 48
1787154978 48
1787154983 48
1787154988 48
1787154993 48
```
</details>

---

