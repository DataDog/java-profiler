---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 04:45:06 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1790325673 32
1790325678 32
1790325683 32
1790325688 32
1790325693 32
1790325698 32
1790325703 32
1790325708 32
1790325713 32
1790325718 32
1790325723 32
1790325728 32
1790325733 32
1790325738 32
1790325743 32
1790325748 32
1790325753 27
1790325758 27
1790325763 27
1790325768 27
```
</details>

---

