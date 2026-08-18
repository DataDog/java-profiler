---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 09:21:54 EDT

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
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787059018 48
1787059023 48
1787059028 48
1787059034 48
1787059039 48
1787059044 48
1787059049 48
1787059054 48
1787059059 48
1787059064 48
1787059069 48
1787059074 48
1787059079 48
1787059084 48
1787059089 48
1787059094 48
1787059099 48
1787059104 47
1787059109 47
1787059114 47
```
</details>

---

