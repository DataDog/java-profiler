---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 14:04:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (6 unique values: 52-76 cores)</summary>

```
1786557621 76
1786557626 76
1786557631 56
1786557636 56
1786557641 54
1786557646 54
1786557651 54
1786557656 52
1786557661 52
1786557666 52
1786557671 52
1786557676 52
1786557681 52
1786557686 54
1786557691 54
1786557696 54
1786557701 54
1786557706 54
1786557711 54
1786557716 58
```
</details>

---

