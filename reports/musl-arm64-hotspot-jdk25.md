---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 06:24:52 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 22-26 cores)</summary>

```
1795778396 22
1795778401 22
1795778406 22
1795778411 22
1795778416 22
1795778421 22
1795778426 22
1795778431 22
1795778436 22
1795778441 22
1795778446 22
1795778451 22
1795778456 22
1795778461 22
1795778466 22
1795778471 22
1795778476 26
1795778481 26
1795778486 26
1795778491 26
```
</details>

---

