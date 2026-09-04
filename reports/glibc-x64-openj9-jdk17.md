---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1788530807 79
1788530812 79
1788530817 79
1788530822 79
1788530827 81
1788530832 81
1788530837 81
1788530842 81
1788530847 81
1788530852 81
1788530857 81
1788530862 81
1788530867 81
1788530872 81
1788530877 81
1788530882 81
1788530887 81
1788530892 81
1788530897 81
1788530902 81
```
</details>

---

