---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 08:01:31 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 13 |
| Allocations | 167 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790596537 48
1790596542 48
1790596547 48
1790596552 48
1790596557 48
1790596562 48
1790596567 48
1790596572 48
1790596577 48
1790596583 48
1790596588 48
1790596593 48
1790596598 48
1790596603 48
1790596608 48
1790596613 48
1790596618 43
1790596623 43
1790596628 43
1790596633 43
```
</details>

---

