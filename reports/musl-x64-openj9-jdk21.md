---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 73-82 cores)</summary>

```
1795434701 80
1795434706 80
1795434711 80
1795434716 80
1795434721 80
1795434726 80
1795434731 80
1795434736 80
1795434741 80
1795434746 80
1795434751 82
1795434756 82
1795434761 82
1795434766 82
1795434771 82
1795434776 82
1795434781 82
1795434786 82
1795434791 82
1795434796 82
```
</details>

---

