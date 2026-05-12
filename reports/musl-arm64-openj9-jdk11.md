---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 09:20:29 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1778591613 51
1778591618 51
1778591623 51
1778591628 51
1778591633 51
1778591638 51
1778591643 55
1778591648 55
1778591653 55
1778591658 55
1778591663 55
1778591668 55
1778591673 55
1778591678 55
1778591683 55
1778591688 55
1778591693 55
1778591698 55
1778591703 59
1778591708 59
```
</details>

---

