---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 10:50:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1778078672 81
1778078677 81
1778078682 79
1778078687 79
1778078692 79
1778078698 79
1778078703 79
1778078708 79
1778078713 77
1778078718 77
1778078723 77
1778078728 77
1778078733 77
1778078738 77
1778078743 77
1778078748 77
1778078753 77
1778078758 75
1778078763 75
1778078768 75
```
</details>

---

