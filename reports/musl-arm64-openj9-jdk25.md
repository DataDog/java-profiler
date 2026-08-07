---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 16:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 13 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (3 unique values: 13-48 cores)</summary>

```
1786134278 48
1786134283 48
1786134288 48
1786134293 48
1786134298 48
1786134303 48
1786134308 48
1786134313 48
1786134318 48
1786134323 48
1786134328 48
1786134333 48
1786134338 48
1786134343 48
1786134348 48
1786134353 48
1786134358 18
1786134363 18
1786134368 18
1786134373 18
```
</details>

---

