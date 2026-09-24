---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 32-64 cores)</summary>

```
1790238295 42
1790238300 32
1790238305 32
1790238310 32
1790238315 32
1790238320 32
1790238325 32
1790238330 32
1790238335 32
1790238340 32
1790238345 32
1790238350 64
1790238355 64
1790238360 64
1790238365 64
1790238370 38
1790238375 38
1790238380 38
1790238385 38
1790238390 38
```
</details>

---

