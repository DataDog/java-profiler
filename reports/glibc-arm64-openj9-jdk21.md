---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:25:24 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 12 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (3 unique values: 41-60 cores)</summary>

```
1795108845 46
1795108850 46
1795108855 46
1795108860 46
1795108865 46
1795108870 41
1795108875 41
1795108880 41
1795108885 41
1795108890 41
1795108895 41
1795108900 41
1795108905 41
1795108910 41
1795108915 41
1795108920 41
1795108925 41
1795108930 46
1795108935 46
1795108940 46
```
</details>

---

