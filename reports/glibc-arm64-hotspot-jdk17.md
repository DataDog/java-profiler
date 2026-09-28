---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 15:07:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1790621803 18
1790621808 18
1790621813 18
1790621818 18
1790621823 18
1790621828 18
1790621834 18
1790621839 18
1790621844 18
1790621849 18
1790621854 18
1790621859 18
1790621864 18
1790621869 18
1790621874 18
1790621879 18
1790621884 18
1790621889 18
1790621894 18
1790621899 18
```
</details>

---

