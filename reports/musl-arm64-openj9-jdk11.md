---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:19:44 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778577269 64
1778577274 64
1778577279 64
1778577284 64
1778577289 64
1778577294 64
1778577299 64
1778577304 64
1778577309 64
1778577314 64
1778577319 64
1778577324 64
1778577329 64
1778577334 64
1778577339 64
1778577344 64
1778577349 64
1778577354 64
1778577359 64
1778577364 64
```
</details>

---

