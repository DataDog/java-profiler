---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:56:44 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 14 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 38-40 cores)</summary>

```
1792403485 40
1792403490 40
1792403495 40
1792403500 39
1792403505 39
1792403510 39
1792403515 39
1792403520 39
1792403525 39
1792403530 39
1792403535 39
1792403540 39
1792403545 39
1792403550 39
1792403555 39
1792403560 38
1792403565 38
1792403570 38
1792403575 38
1792403580 38
```
</details>

---

