---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 07:16:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1786446603 52
1786446608 52
1786446613 52
1786446618 52
1786446623 52
1786446628 52
1786446633 52
1786446638 52
1786446643 52
1786446648 52
1786446653 52
1786446658 52
1786446663 52
1786446668 52
1786446673 52
1786446678 32
1786446683 32
1786446688 32
1786446694 32
1786446699 32
```
</details>

---

