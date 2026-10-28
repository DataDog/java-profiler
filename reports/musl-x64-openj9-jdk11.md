---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 13:11:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793207203 32
1793207208 32
1793207213 32
1793207218 32
1793207223 32
1793207228 32
1793207233 32
1793207238 32
1793207243 32
1793207248 32
1793207253 32
1793207258 32
1793207263 32
1793207268 32
1793207273 32
1793207278 32
1793207283 32
1793207288 32
1793207293 32
1793207298 32
```
</details>

---

