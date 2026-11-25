---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:33:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 83 |
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
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 83-92 cores)</summary>

```
1795631263 92
1795631268 92
1795631273 92
1795631278 92
1795631283 92
1795631288 92
1795631293 92
1795631298 92
1795631303 92
1795631308 92
1795631313 85
1795631318 85
1795631323 85
1795631328 85
1795631333 85
1795631338 85
1795631343 85
1795631348 85
1795631353 85
1795631358 85
```
</details>

---

