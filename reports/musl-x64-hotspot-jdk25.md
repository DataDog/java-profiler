---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 09:00:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 64-89 cores)</summary>

```
1786020953 64
1786020958 64
1786020963 64
1786020968 64
1786020973 89
1786020978 89
1786020983 89
1786020988 89
1786020993 86
1786020998 86
1786021003 86
1786021008 86
1786021013 86
1786021018 86
1786021023 86
1786021028 86
1786021033 86
1786021038 86
1786021043 86
1786021048 86
```
</details>

---

