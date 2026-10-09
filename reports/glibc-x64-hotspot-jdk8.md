---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 44-65 cores)</summary>

```
1791543739 52
1791543744 52
1791543749 52
1791543754 52
1791543759 52
1791543764 52
1791543769 52
1791543774 44
1791543779 44
1791543784 65
1791543789 65
1791543794 65
1791543799 65
1791543804 65
1791543809 65
1791543814 45
1791543819 45
1791543824 45
1791543829 45
1791543834 45
```
</details>

---

