---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 00:57:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 988 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1787547213 47
1787547218 49
1787547223 49
1787547228 51
1787547233 51
1787547239 51
1787547244 51
1787547249 51
1787547254 51
1787547259 51
1787547264 51
1787547269 51
1787547274 51
1787547279 51
1787547284 51
1787547289 51
1787547294 51
1787547299 51
1787547304 51
1787547309 51
```
</details>

---

