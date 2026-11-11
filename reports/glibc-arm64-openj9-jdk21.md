---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:26:45 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (4 unique values: 55-64 cores)</summary>

```
1794406971 56
1794406976 56
1794406981 56
1794406986 56
1794406991 55
1794406996 55
1794407001 55
1794407006 55
1794407011 55
1794407016 55
1794407021 55
1794407026 55
1794407031 55
1794407036 55
1794407041 56
1794407046 56
1794407051 56
1794407056 56
1794407061 56
1794407066 59
```
</details>

---

