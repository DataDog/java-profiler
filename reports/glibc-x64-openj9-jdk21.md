---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 12:26:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 20-29 cores)</summary>

```
1792599668 29
1792599673 29
1792599678 29
1792599683 29
1792599688 29
1792599693 29
1792599698 29
1792599703 29
1792599708 29
1792599713 29
1792599718 29
1792599723 27
1792599728 27
1792599733 25
1792599738 25
1792599743 25
1792599748 25
1792599753 27
1792599758 27
1792599763 25
```
</details>

---

