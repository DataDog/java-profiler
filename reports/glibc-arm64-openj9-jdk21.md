---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 18:16:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 52-64 cores)</summary>

```
1792534370 53
1792534375 64
1792534380 64
1792534385 64
1792534390 64
1792534395 64
1792534400 64
1792534406 64
1792534411 64
1792534416 64
1792534421 64
1792534426 64
1792534431 64
1792534436 64
1792534441 52
1792534446 52
1792534451 52
1792534456 52
1792534461 52
1792534466 52
```
</details>

---

