---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:13:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (4 unique values: 49-59 cores)</summary>

```
1795529409 59
1795529414 59
1795529419 55
1795529424 55
1795529429 49
1795529434 49
1795529440 49
1795529445 49
1795529450 49
1795529455 49
1795529460 49
1795529465 49
1795529470 49
1795529475 49
1795529480 49
1795529485 54
1795529490 54
1795529495 54
1795529500 54
1795529505 54
```
</details>

---

