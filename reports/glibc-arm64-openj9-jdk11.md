---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:48:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790570648 43
1790570653 43
1790570658 43
1790570663 43
1790570668 43
1790570673 43
1790570678 43
1790570683 43
1790570688 43
1790570693 43
1790570698 43
1790570703 43
1790570708 48
1790570713 48
1790570718 48
1790570723 48
1790570728 48
1790570733 48
1790570738 48
1790570743 48
```
</details>

---

