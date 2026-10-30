---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:45:19 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1793367709 48
1793367714 46
1793367719 46
1793367724 46
1793367729 46
1793367734 46
1793367739 46
1793367744 46
1793367749 46
1793367754 46
1793367759 46
1793367764 46
1793367769 46
1793367774 46
1793367779 46
1793367784 41
1793367789 41
1793367794 41
1793367799 41
1793367804 41
```
</details>

---

