---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 12:18:21 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1792512711 84
1792512716 84
1792512721 84
1792512726 84
1792512731 84
1792512736 84
1792512741 84
1792512746 84
1792512751 84
1792512756 84
1792512761 84
1792512766 84
1792512771 84
1792512776 84
1792512781 82
1792512786 82
1792512791 82
1792512796 82
1792512801 82
1792512806 82
```
</details>

---

