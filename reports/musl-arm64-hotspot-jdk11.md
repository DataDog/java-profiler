---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:53:28 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 11 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1793288628 32
1793288633 32
1793288638 32
1793288643 32
1793288648 32
1793288653 32
1793288658 32
1793288663 34
1793288668 34
1793288673 34
1793288678 34
1793288683 34
1793288688 34
1793288693 34
1793288698 34
1793288703 34
1793288708 34
1793288713 34
1793288718 34
1793288723 34
```
</details>

---

