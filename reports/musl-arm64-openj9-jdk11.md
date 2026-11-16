---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1794850178 25
1794850183 25
1794850188 38
1794850193 38
1794850198 38
1794850203 38
1794850208 38
1794850213 38
1794850218 38
1794850223 38
1794850228 38
1794850233 38
1794850238 38
1794850243 38
1794850248 38
1794850253 38
1794850258 38
1794850263 38
1794850268 38
1794850273 38
```
</details>

---

