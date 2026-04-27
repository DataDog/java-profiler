---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 05:15:08 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 14 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777280993 59
1777280998 59
1777281003 59
1777281008 59
1777281013 64
1777281018 64
1777281023 64
1777281028 64
1777281033 64
1777281038 64
1777281043 64
1777281049 64
1777281054 64
1777281059 64
1777281064 64
1777281069 64
1777281074 64
1777281079 64
1777281084 64
1777281089 64
```
</details>

---

