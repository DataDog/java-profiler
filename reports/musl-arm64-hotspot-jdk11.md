---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 12:33:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 7 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1791476912 37
1791476917 37
1791476922 37
1791476927 37
1791476932 37
1791476937 37
1791476943 37
1791476948 37
1791476953 37
1791476958 37
1791476963 37
1791476968 37
1791476973 37
1791476978 37
1791476983 42
1791476988 42
1791476993 42
1791476998 42
1791477003 42
1791477008 42
```
</details>

---

