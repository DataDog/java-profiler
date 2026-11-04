---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 20:28:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793755486 48
1793755492 48
1793755497 48
1793755502 48
1793755507 48
1793755512 48
1793755517 48
1793755522 48
1793755527 48
1793755532 48
1793755537 48
1793755542 48
1793755547 48
1793755552 48
1793755557 48
1793755562 48
1793755567 48
1793755572 48
1793755577 48
1793755582 48
```
</details>

---

