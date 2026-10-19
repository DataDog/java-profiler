---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1145 |
| Sample Rate | 19.08/sec |
| Health Score | 1192% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792403391 51
1792403396 51
1792403401 51
1792403406 51
1792403411 64
1792403416 64
1792403421 64
1792403426 64
1792403431 64
1792403436 64
1792403441 64
1792403446 64
1792403451 64
1792403456 64
1792403461 64
1792403466 64
1792403471 64
1792403476 64
1792403481 64
1792403486 64
```
</details>

---

