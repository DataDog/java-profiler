---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 11:36:51 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1790782289 45
1790782294 45
1790782299 44
1790782304 44
1790782309 44
1790782314 44
1790782319 37
1790782324 37
1790782329 37
1790782334 37
1790782339 37
1790782344 37
1790782349 37
1790782354 37
1790782359 37
1790782364 37
1790782369 39
1790782374 39
1790782379 39
1790782384 39
```
</details>

---

