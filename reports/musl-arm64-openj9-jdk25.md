---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 12 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1795613514 45
1795613519 45
1795613524 45
1795613529 45
1795613534 45
1795613539 45
1795613544 45
1795613549 45
1795613554 45
1795613559 47
1795613564 47
1795613569 47
1795613574 47
1795613579 47
1795613584 47
1795613589 47
1795613594 47
1795613599 47
1795613604 47
1795613609 47
```
</details>

---

