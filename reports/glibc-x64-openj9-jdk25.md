---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-12 10:34:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 10 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 12 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 72-82 cores)</summary>

```
1773325705 82
1773325710 82
1773325715 82
1773325720 82
1773325725 82
1773325730 82
1773325735 82
1773325740 82
1773325745 82
1773325750 82
1773325755 82
1773325760 82
1773325765 82
1773325770 82
1773325775 82
1773325780 82
1773325785 82
1773325790 82
1773325795 72
1773325800 72
```
</details>

---

