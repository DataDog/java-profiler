---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:38:09 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 15-18 cores)</summary>

```
1794832452 16
1794832457 16
1794832462 16
1794832467 16
1794832472 16
1794832477 16
1794832482 16
1794832487 16
1794832492 16
1794832497 16
1794832502 16
1794832507 16
1794832512 18
1794832517 18
1794832522 18
1794832527 18
1794832532 18
1794832537 18
1794832542 15
1794832547 15
```
</details>

---

