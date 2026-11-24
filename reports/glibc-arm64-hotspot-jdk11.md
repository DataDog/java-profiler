---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:41:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795545472 48
1795545477 48
1795545482 48
1795545487 48
1795545492 48
1795545497 48
1795545502 48
1795545507 48
1795545512 48
1795545517 48
1795545522 48
1795545527 48
1795545532 48
1795545537 48
1795545542 64
1795545547 64
1795545552 64
1795545557 64
1795545562 64
1795545567 64
```
</details>

---

