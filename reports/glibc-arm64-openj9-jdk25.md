---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:45:19 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1793367719 35
1793367724 35
1793367729 35
1793367734 35
1793367739 35
1793367744 35
1793367749 35
1793367754 35
1793367759 35
1793367764 35
1793367769 35
1793367774 35
1793367779 35
1793367784 35
1793367789 35
1793367794 35
1793367799 35
1793367804 40
1793367809 40
1793367814 40
```
</details>

---

