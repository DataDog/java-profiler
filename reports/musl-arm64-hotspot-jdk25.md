---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:27:27 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 10 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1789680036 40
1789680041 40
1789680046 37
1789680051 37
1789680056 37
1789680061 37
1789680066 37
1789680071 37
1789680076 37
1789680081 37
1789680086 37
1789680091 37
1789680096 37
1789680101 37
1789680106 37
1789680111 37
1789680116 37
1789680121 37
1789680126 37
1789680131 37
```
</details>

---

