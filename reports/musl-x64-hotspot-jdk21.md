---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (6 unique values: 58-79 cores)</summary>

```
1777477264 66
1777477269 67
1777477274 67
1777477279 67
1777477284 60
1777477289 60
1777477294 62
1777477299 62
1777477304 62
1777477309 62
1777477314 62
1777477319 62
1777477324 62
1777477329 58
1777477334 58
1777477339 58
1777477344 67
1777477349 67
1777477354 67
1777477359 67
```
</details>

---

