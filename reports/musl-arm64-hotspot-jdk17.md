---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:39:37 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 46-56 cores)</summary>

```
1791531253 56
1791531258 56
1791531263 56
1791531268 56
1791531273 56
1791531278 56
1791531283 56
1791531288 56
1791531293 56
1791531298 56
1791531303 56
1791531308 56
1791531313 56
1791531318 56
1791531323 54
1791531328 54
1791531333 54
1791531338 54
1791531343 54
1791531348 54
```
</details>

---

