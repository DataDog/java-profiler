---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 10:02:49 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 13 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1787320593 48
1787320598 48
1787320603 48
1787320608 48
1787320613 48
1787320618 48
1787320623 48
1787320628 48
1787320633 48
1787320638 48
1787320643 48
1787320648 48
1787320653 48
1787320658 48
1787320663 48
1787320668 36
1787320673 36
1787320678 36
1787320683 36
1787320688 36
```
</details>

---

