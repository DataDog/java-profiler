---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:15:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795108264 50
1795108269 50
1795108274 50
1795108279 50
1795108284 50
1795108289 50
1795108294 50
1795108299 50
1795108304 50
1795108309 50
1795108314 50
1795108319 50
1795108324 50
1795108329 50
1795108334 50
1795108339 50
1795108344 50
1795108349 50
1795108354 50
1795108359 50
```
</details>

---

