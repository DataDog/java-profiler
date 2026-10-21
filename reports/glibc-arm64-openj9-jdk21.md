---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 12:26:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1792599653 31
1792599658 31
1792599663 31
1792599668 31
1792599673 31
1792599678 31
1792599683 36
1792599688 36
1792599693 36
1792599698 36
1792599703 36
1792599708 36
1792599713 36
1792599718 36
1792599723 36
1792599728 36
1792599733 36
1792599738 36
1792599743 36
1792599748 36
```
</details>

---

