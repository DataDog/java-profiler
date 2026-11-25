---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:36:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795620722 70
1795620727 70
1795620732 70
1795620737 70
1795620742 70
1795620747 70
1795620752 72
1795620757 72
1795620762 72
1795620767 72
1795620772 72
1795620777 72
1795620782 72
1795620787 72
1795620792 72
1795620797 72
1795620802 72
1795620807 72
1795620812 72
1795620817 72
```
</details>

---

