---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 13 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 37-57 cores)</summary>

```
1770130508 37
1770130513 37
1770130518 37
1770130523 37
1770130528 37
1770130533 37
1770130538 37
1770130543 37
1770130548 37
1770130553 37
1770130558 57
1770130563 57
1770130568 57
1770130573 57
1770130578 57
1770130583 57
1770130588 57
1770130593 57
1770130598 57
1770130603 57
```
</details>

---

