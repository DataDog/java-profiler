---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 12:17:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (3 unique values: 61-64 cores)</summary>

```
1787242367 62
1787242372 62
1787242377 62
1787242382 62
1787242387 62
1787242392 62
1787242397 62
1787242402 62
1787242407 62
1787242412 62
1787242417 62
1787242422 62
1787242427 62
1787242432 62
1787242437 62
1787242442 62
1787242447 64
1787242452 64
1787242457 61
1787242462 61
```
</details>

---

