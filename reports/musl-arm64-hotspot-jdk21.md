---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 20:57:23 EDT

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
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 12 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787705558 32
1787705563 32
1787705568 32
1787705573 32
1787705578 32
1787705583 32
1787705588 32
1787705593 32
1787705598 32
1787705603 32
1787705608 32
1787705613 32
1787705618 32
1787705623 32
1787705628 32
1787705633 32
1787705638 32
1787705643 32
1787705648 32
1787705653 32
```
</details>

---

