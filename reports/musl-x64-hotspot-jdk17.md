---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1790074847 70
1790074852 70
1790074857 70
1790074862 70
1790074867 70
1790074872 70
1790074877 70
1790074882 70
1790074887 72
1790074892 72
1790074897 72
1790074902 72
1790074907 72
1790074912 72
1790074917 72
1790074922 70
1790074927 70
1790074932 70
1790074937 70
1790074942 70
```
</details>

---

