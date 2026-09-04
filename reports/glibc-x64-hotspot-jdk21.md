---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-04 10:11:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1788530792 96
1788530797 96
1788530802 96
1788530807 96
1788530812 96
1788530817 96
1788530822 91
1788530827 91
1788530832 91
1788530837 91
1788530842 91
1788530847 91
1788530852 91
1788530857 91
1788530862 91
1788530867 91
1788530872 91
1788530877 91
1788530882 91
1788530887 91
```
</details>

---

