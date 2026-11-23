---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 00:00:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795409788 62
1795409793 62
1795409798 62
1795409803 62
1795409808 62
1795409813 62
1795409818 62
1795409823 62
1795409828 62
1795409833 62
1795409838 62
1795409843 62
1795409848 62
1795409853 62
1795409858 62
1795409863 64
1795409868 64
1795409873 64
1795409879 64
1795409884 64
```
</details>

---

