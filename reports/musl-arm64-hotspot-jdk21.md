---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-13 07:32:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 10 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1778671548 32
1778671553 32
1778671558 32
1778671563 32
1778671568 32
1778671573 32
1778671578 32
1778671583 32
1778671588 36
1778671593 36
1778671598 36
1778671603 36
1778671608 36
1778671613 36
1778671618 36
1778671623 36
1778671628 36
1778671633 36
1778671638 36
1778671643 36
```
</details>

---

