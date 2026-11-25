---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:33:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 71-87 cores)</summary>

```
1795631263 87
1795631268 87
1795631273 87
1795631278 87
1795631283 87
1795631288 87
1795631293 87
1795631298 87
1795631303 87
1795631308 87
1795631313 87
1795631318 87
1795631323 87
1795631328 87
1795631333 87
1795631338 87
1795631343 85
1795631348 85
1795631353 85
1795631358 85
```
</details>

---

