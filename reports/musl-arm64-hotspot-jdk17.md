---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:50 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 37 |
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
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 34-37 cores)</summary>

```
1792686982 34
1792686987 34
1792686992 34
1792686997 34
1792687002 34
1792687007 34
1792687012 34
1792687017 34
1792687022 37
1792687027 37
1792687032 37
1792687037 37
1792687042 37
1792687047 37
1792687052 37
1792687057 37
1792687062 37
1792687067 37
1792687072 37
1792687077 37
```
</details>

---

