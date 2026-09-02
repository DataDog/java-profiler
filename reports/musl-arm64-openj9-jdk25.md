---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 05:49:13 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1788342315 46
1788342320 46
1788342325 46
1788342330 46
1788342335 46
1788342340 46
1788342345 46
1788342350 46
1788342355 46
1788342360 46
1788342365 46
1788342370 48
1788342375 48
1788342380 48
1788342385 48
1788342390 48
1788342395 48
1788342400 47
1788342405 47
1788342410 47
```
</details>

---

