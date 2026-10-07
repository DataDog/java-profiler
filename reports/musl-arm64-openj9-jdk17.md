---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791391364 51
1791391369 51
1791391374 51
1791391379 51
1791391384 51
1791391389 51
1791391394 51
1791391399 51
1791391404 51
1791391409 46
1791391414 46
1791391419 46
1791391424 46
1791391429 46
1791391434 46
1791391439 46
1791391444 46
1791391449 46
1791391454 46
1791391459 46
```
</details>

---

