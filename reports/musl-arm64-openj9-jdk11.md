---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:07:36 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (5 unique values: 36-43 cores)</summary>

```
1793372527 42
1793372532 42
1793372537 42
1793372542 42
1793372547 42
1793372552 42
1793372557 43
1793372562 43
1793372567 42
1793372572 42
1793372577 42
1793372583 42
1793372588 38
1793372593 38
1793372598 38
1793372603 38
1793372608 38
1793372613 38
1793372618 38
1793372623 38
```
</details>

---

