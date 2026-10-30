---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:45:20 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 54-58 cores)</summary>

```
1793367685 58
1793367690 58
1793367695 58
1793367700 58
1793367705 58
1793367710 58
1793367715 58
1793367721 58
1793367726 58
1793367731 58
1793367736 56
1793367741 56
1793367746 56
1793367751 56
1793367756 56
1793367761 56
1793367766 56
1793367771 54
1793367776 54
1793367781 54
```
</details>

---

