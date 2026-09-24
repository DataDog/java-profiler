---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-24 04:40:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1790238913 64
1790238918 64
1790238923 64
1790238928 64
1790238933 64
1790238938 64
1790238943 64
1790238948 64
1790238953 64
1790238958 64
1790238963 64
1790238968 54
1790238973 54
1790238978 54
1790238983 54
1790238988 54
1790238993 54
1790238998 54
1790239003 54
1790239008 54
```
</details>

---

