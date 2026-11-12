---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:21:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 62-79 cores)</summary>

```
1794478561 63
1794478566 63
1794478571 63
1794478576 63
1794478581 63
1794478586 63
1794478591 67
1794478596 67
1794478601 67
1794478606 67
1794478611 62
1794478616 62
1794478621 62
1794478626 62
1794478631 62
1794478636 62
1794478641 62
1794478646 62
1794478651 62
1794478657 79
```
</details>

---

