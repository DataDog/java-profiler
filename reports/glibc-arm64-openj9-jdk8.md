---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-06 14:10:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1778090728 49
1778090733 49
1778090738 49
1778090743 49
1778090748 49
1778090753 49
1778090758 49
1778090763 49
1778090768 49
1778090773 49
1778090778 49
1778090784 49
1778090789 49
1778090794 49
1778090799 49
1778090804 49
1778090809 49
1778090814 49
1778090819 49
1778090824 54
```
</details>

---

