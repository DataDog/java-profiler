---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 10:02:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787320588 64
1787320593 64
1787320598 64
1787320603 64
1787320608 64
1787320613 64
1787320618 64
1787320623 64
1787320628 64
1787320633 64
1787320638 64
1787320643 64
1787320648 64
1787320653 64
1787320658 64
1787320663 64
1787320668 64
1787320673 64
1787320678 64
1787320683 64
```
</details>

---

