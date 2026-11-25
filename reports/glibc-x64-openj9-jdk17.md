---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:33:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 50-66 cores)</summary>

```
1795631278 50
1795631283 50
1795631288 50
1795631293 50
1795631298 50
1795631303 50
1795631308 50
1795631313 50
1795631318 50
1795631323 66
1795631328 66
1795631333 66
1795631338 66
1795631343 66
1795631348 57
1795631353 57
1795631358 59
1795631363 59
1795631368 59
1795631373 59
```
</details>

---

