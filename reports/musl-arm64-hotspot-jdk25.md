---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-17 12:52:31 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 10 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794937494 33
1794937499 33
1794937504 33
1794937509 38
1794937514 38
1794937519 38
1794937524 38
1794937529 38
1794937534 38
1794937539 38
1794937544 38
1794937550 38
1794937555 38
1794937560 38
1794937565 38
1794937570 38
1794937575 38
1794937580 38
1794937585 38
1794937590 38
```
</details>

---

