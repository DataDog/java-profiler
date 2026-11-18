---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:35:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 39-49 cores)</summary>

```
1794997773 41
1794997778 41
1794997783 41
1794997788 39
1794997793 39
1794997798 39
1794997803 39
1794997808 39
1794997813 39
1794997818 39
1794997823 39
1794997828 39
1794997833 39
1794997838 39
1794997843 39
1794997848 41
1794997853 41
1794997858 41
1794997863 41
1794997868 41
```
</details>

---

