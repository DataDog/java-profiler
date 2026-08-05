---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:02 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1785932432 43
1785932437 43
1785932442 43
1785932447 43
1785932452 43
1785932457 43
1785932462 43
1785932467 43
1785932472 43
1785932477 43
1785932482 43
1785932487 43
1785932492 43
1785932497 43
1785932502 43
1785932507 43
1785932512 43
1785932517 43
1785932522 43
1785932527 43
```
</details>

---

