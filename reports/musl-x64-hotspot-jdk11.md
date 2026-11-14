---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:56:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794682213 94
1794682218 94
1794682223 94
1794682228 94
1794682233 94
1794682238 94
1794682243 94
1794682248 92
1794682253 92
1794682258 92
1794682263 92
1794682268 94
1794682273 94
1794682278 94
1794682283 94
1794682288 96
1794682293 96
1794682298 96
1794682303 96
1794682308 96
```
</details>

---

