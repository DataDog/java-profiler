---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:06:58 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 11 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 36-51 cores)</summary>

```
1794434521 50
1794434526 50
1794434531 50
1794434536 50
1794434541 51
1794434546 51
1794434551 51
1794434556 51
1794434561 51
1794434566 51
1794434571 39
1794434576 39
1794434581 39
1794434586 39
1794434591 39
1794434596 39
1794434601 39
1794434606 39
1794434611 39
1794434616 39
```
</details>

---

