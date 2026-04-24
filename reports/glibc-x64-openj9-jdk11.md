---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 08:33:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 76-77 cores)</summary>

```
1777033674 77
1777033679 77
1777033684 76
1777033689 76
1777033694 76
1777033699 76
1777033704 76
1777033709 76
1777033714 76
1777033719 76
1777033724 76
1777033729 76
1777033734 76
1777033739 76
1777033744 76
1777033749 76
1777033754 76
1777033759 76
1777033764 76
1777033769 76
```
</details>

---

