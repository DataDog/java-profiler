---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:37:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1792675920 45
1792675925 45
1792675930 45
1792675935 45
1792675940 45
1792675945 45
1792675950 45
1792675955 45
1792675960 45
1792675965 47
1792675970 47
1792675975 47
1792675980 47
1792675985 47
1792675990 47
1792675995 47
1792676000 47
1792676005 47
1792676010 47
1792676015 47
```
</details>

---

