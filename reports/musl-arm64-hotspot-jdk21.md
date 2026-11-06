---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-06 00:04:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793941191 48
1793941196 48
1793941201 48
1793941206 43
1793941211 43
1793941216 38
1793941221 38
1793941226 38
1793941232 38
1793941237 38
1793941242 38
1793941247 38
1793941252 38
1793941257 38
1793941262 38
1793941267 38
1793941272 38
1793941277 38
1793941282 38
1793941287 38
```
</details>

---

