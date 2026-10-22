---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:37:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1792675915 72
1792675920 72
1792675925 72
1792675930 72
1792675935 72
1792675940 72
1792675945 74
1792675950 74
1792675955 74
1792675960 74
1792675965 74
1792675970 74
1792675975 74
1792675980 74
1792675985 74
1792675990 72
1792675995 72
1792676000 72
1792676005 72
1792676010 72
```
</details>

---

