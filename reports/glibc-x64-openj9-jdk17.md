---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:32:53 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 10 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 40-64 cores)</summary>

```
1790093815 40
1790093820 40
1790093825 40
1790093830 64
1790093835 64
1790093841 40
1790093846 40
1790093851 40
1790093856 40
1790093861 40
1790093866 40
1790093871 40
1790093876 40
1790093881 40
1790093886 40
1790093891 40
1790093896 40
1790093901 40
1790093906 40
1790093911 40
```
</details>

---

