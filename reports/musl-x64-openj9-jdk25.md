---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:12:34 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1795097239 65
1795097244 65
1795097249 72
1795097254 72
1795097259 72
1795097264 72
1795097269 72
1795097274 72
1795097279 72
1795097284 72
1795097289 72
1795097294 72
1795097299 70
1795097304 70
1795097309 70
1795097314 68
1795097319 68
1795097324 68
1795097329 68
1795097334 68
```
</details>

---

