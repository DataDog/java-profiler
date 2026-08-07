---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 00:56:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786078354 34
1786078359 34
1786078364 34
1786078369 34
1786078374 34
1786078379 34
1786078384 34
1786078389 34
1786078394 34
1786078399 34
1786078404 34
1786078409 34
1786078414 34
1786078419 34
1786078424 34
1786078429 34
1786078434 34
1786078439 34
1786078444 32
1786078449 32
```
</details>

---

