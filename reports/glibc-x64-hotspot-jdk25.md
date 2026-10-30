---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:45:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1793367684 57
1793367689 57
1793367694 57
1793367699 57
1793367704 57
1793367709 57
1793367714 57
1793367719 55
1793367724 55
1793367729 55
1793367734 55
1793367739 57
1793367744 57
1793367749 57
1793367754 57
1793367759 57
1793367764 57
1793367769 59
1793367774 59
1793367779 59
```
</details>

---

