---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:33:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 58-78 cores)</summary>

```
1795631248 58
1795631253 67
1795631258 67
1795631263 67
1795631268 67
1795631273 67
1795631278 67
1795631283 67
1795631288 67
1795631293 58
1795631298 58
1795631303 75
1795631308 75
1795631313 75
1795631318 75
1795631323 75
1795631328 75
1795631333 75
1795631338 75
1795631343 75
```
</details>

---

