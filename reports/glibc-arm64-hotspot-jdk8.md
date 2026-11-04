---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-03 20:28:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 1 |
| Sample Rate | 0.02/sec |
| Health Score | 1% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 26-26 cores)</summary>

```
1793755450 26
1793755455 26
1793755460 26
1793755465 26
1793755470 26
1793755475 26
1793755480 26
1793755485 26
1793755490 26
1793755495 26
1793755500 26
1793755505 26
1793755510 26
1793755515 26
1793755520 26
1793755525 26
1793755530 26
1793755535 26
1793755540 26
1793755545 26
```
</details>

---

