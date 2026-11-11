---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:10:50 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1794355404 47
1794355409 47
1794355414 47
1794355419 47
1794355424 47
1794355429 47
1794355434 47
1794355439 47
1794355444 47
1794355449 47
1794355454 47
1794355459 47
1794355464 47
1794355469 47
1794355474 47
1794355479 47
1794355484 42
1794355489 42
1794355494 42
1794355499 42
```
</details>

---

