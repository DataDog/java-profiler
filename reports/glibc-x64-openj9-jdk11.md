---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-01 01:04:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793509234 51
1793509239 51
1793509244 49
1793509249 49
1793509254 49
1793509259 49
1793509264 49
1793509269 49
1793509274 49
1793509280 49
1793509285 49
1793509290 49
1793509295 49
1793509300 49
1793509305 49
1793509310 49
1793509315 49
1793509320 49
1793509325 49
1793509330 49
```
</details>

---

