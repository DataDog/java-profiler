---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:33:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 59-70 cores)</summary>

```
1795631253 70
1795631258 70
1795631263 70
1795631268 70
1795631273 70
1795631278 70
1795631283 70
1795631288 68
1795631293 68
1795631298 68
1795631303 68
1795631308 59
1795631313 59
1795631318 59
1795631323 59
1795631328 59
1795631333 59
1795631338 59
1795631343 59
1795631348 59
```
</details>

---

