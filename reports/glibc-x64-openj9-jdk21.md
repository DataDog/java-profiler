---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 78-96 cores)</summary>

```
1788530787 78
1788530792 78
1788530797 78
1788530802 78
1788530807 78
1788530812 78
1788530817 78
1788530822 78
1788530827 78
1788530832 78
1788530837 83
1788530842 83
1788530847 83
1788530852 83
1788530857 83
1788530862 83
1788530867 91
1788530872 91
1788530877 91
1788530882 96
```
</details>

---

