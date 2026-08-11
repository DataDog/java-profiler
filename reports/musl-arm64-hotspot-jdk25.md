---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:42 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786446583 53
1786446588 53
1786446593 53
1786446598 53
1786446603 53
1786446608 53
1786446613 53
1786446618 53
1786446623 53
1786446628 53
1786446633 53
1786446638 53
1786446643 53
1786446648 53
1786446653 53
1786446658 53
1786446663 48
1786446668 48
1786446673 48
1786446678 48
```
</details>

---

