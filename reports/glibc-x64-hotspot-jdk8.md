---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1790074857 64
1790074862 64
1790074867 64
1790074872 64
1790074877 64
1790074882 64
1790074887 64
1790074892 64
1790074897 64
1790074902 64
1790074907 64
1790074912 64
1790074917 64
1790074922 64
1790074927 64
1790074932 64
1790074937 64
1790074942 64
1790074947 62
1790074952 62
```
</details>

---

