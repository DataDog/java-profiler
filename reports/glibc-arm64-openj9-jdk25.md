---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:47:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 14 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790091729 48
1790091734 48
1790091739 48
1790091744 48
1790091749 48
1790091754 48
1790091759 48
1790091764 48
1790091769 48
1790091774 48
1790091779 48
1790091784 48
1790091789 48
1790091794 48
1790091799 48
1790091804 38
1790091809 38
1790091814 38
1790091819 38
1790091824 38
```
</details>

---

