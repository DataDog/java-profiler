---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 19:21:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 76-93 cores)</summary>

```
1794788186 93
1794788191 93
1794788196 93
1794788201 93
1794788206 93
1794788211 93
1794788216 93
1794788221 93
1794788226 76
1794788231 76
1794788236 76
1794788241 76
1794788246 76
1794788251 76
1794788256 76
1794788261 76
1794788266 76
1794788271 76
1794788276 76
1794788281 76
```
</details>

---

