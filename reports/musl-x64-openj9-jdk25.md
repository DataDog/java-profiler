---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 11:13:23 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 11 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 41-60 cores)</summary>

```
1772813274 60
1772813279 60
1772813284 60
1772813289 55
1772813294 55
1772813299 55
1772813304 55
1772813309 55
1772813314 55
1772813319 55
1772813324 55
1772813329 42
1772813334 42
1772813339 41
1772813344 41
1772813349 41
1772813354 41
1772813359 41
1772813364 41
1772813369 41
```
</details>

---

