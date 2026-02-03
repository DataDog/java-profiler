---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (6 unique values: 40-52 cores)</summary>

```
1770135199 52
1770135204 52
1770135209 52
1770135214 52
1770135219 52
1770135224 52
1770135229 43
1770135234 43
1770135239 48
1770135244 48
1770135249 48
1770135254 46
1770135259 46
1770135264 45
1770135269 45
1770135274 40
1770135279 40
1770135284 40
1770135289 40
1770135294 40
```
</details>

---

