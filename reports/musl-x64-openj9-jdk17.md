---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:24:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (6 unique values: 62-92 cores)</summary>

```
1795195203 82
1795195208 82
1795195213 82
1795195218 82
1795195223 82
1795195228 82
1795195233 82
1795195238 82
1795195243 82
1795195248 82
1795195253 85
1795195258 85
1795195263 85
1795195268 83
1795195274 83
1795195279 92
1795195284 92
1795195289 92
1795195294 92
1795195299 64
```
</details>

---

