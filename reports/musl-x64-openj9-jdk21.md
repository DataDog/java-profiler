---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-23 00:55:51 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1787460703 61
1787460708 61
1787460713 61
1787460718 61
1787460723 61
1787460728 59
1787460733 59
1787460738 59
1787460743 59
1787460748 59
1787460753 59
1787460758 59
1787460763 59
1787460768 59
1787460773 59
1787460778 59
1787460783 61
1787460788 61
1787460793 61
1787460798 61
```
</details>

---

