---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 06:41:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 86-90 cores)</summary>

```
1791196678 86
1791196683 86
1791196688 86
1791196693 86
1791196698 86
1791196703 86
1791196708 86
1791196713 86
1791196718 86
1791196723 86
1791196728 86
1791196733 86
1791196738 90
1791196743 90
1791196748 90
1791196753 90
1791196758 90
1791196763 86
1791196768 86
1791196773 86
```
</details>

---

