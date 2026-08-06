---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 09:00:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1786020943 88
1786020948 86
1786020953 86
1786020958 86
1786020963 86
1786020968 86
1786020973 86
1786020978 86
1786020983 86
1786020988 86
1786020993 86
1786020998 86
1786021003 86
1786021008 86
1786021013 86
1786021018 86
1786021023 86
1786021028 84
1786021033 84
1786021038 84
```
</details>

---

