---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 03:32:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 46-59 cores)</summary>

```
1794990490 46
1794990496 46
1794990501 46
1794990506 46
1794990511 46
1794990516 46
1794990521 46
1794990526 46
1794990531 46
1794990536 46
1794990541 46
1794990546 46
1794990551 46
1794990556 59
1794990561 59
1794990566 59
1794990571 59
1794990576 59
1794990581 59
1794990586 59
```
</details>

---

