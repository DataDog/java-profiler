---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:33:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1795631262 92
1795631267 94
1795631272 94
1795631277 94
1795631282 94
1795631287 94
1795631292 94
1795631297 94
1795631302 94
1795631307 94
1795631312 94
1795631317 94
1795631322 94
1795631327 94
1795631332 94
1795631337 94
1795631342 96
1795631347 96
1795631352 96
1795631357 96
```
</details>

---

