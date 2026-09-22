---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 09:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1790084797 59
1790084802 59
1790084807 59
1790084812 59
1790084817 59
1790084822 59
1790084827 59
1790084832 59
1790084837 59
1790084842 59
1790084847 64
1790084852 64
1790084857 64
1790084862 64
1790084867 64
1790084872 64
1790084877 64
1790084882 64
1790084887 64
1790084892 64
```
</details>

---

