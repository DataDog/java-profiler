---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 08:59:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 11 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (3 unique values: 18-23 cores)</summary>

```
1786020948 18
1786020953 18
1786020958 18
1786020963 18
1786020968 18
1786020973 18
1786020978 18
1786020983 18
1786020988 23
1786020993 23
1786020998 23
1786021003 23
1786021009 23
1786021014 23
1786021019 23
1786021024 23
1786021029 23
1786021034 23
1786021039 23
1786021044 23
```
</details>

---

