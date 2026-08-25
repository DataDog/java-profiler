---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 16:41:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787690230 96
1787690235 96
1787690240 96
1787690245 96
1787690250 96
1787690255 96
1787690260 96
1787690265 96
1787690270 96
1787690275 94
1787690280 94
1787690285 94
1787690290 94
1787690295 94
1787690300 96
1787690305 96
1787690310 96
1787690315 96
1787690320 96
1787690325 96
```
</details>

---

