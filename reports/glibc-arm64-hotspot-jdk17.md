---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 09:37:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 61-64 cores)</summary>

```
1788528818 61
1788528823 61
1788528828 61
1788528833 61
1788528838 61
1788528843 61
1788528848 61
1788528853 61
1788528858 61
1788528863 61
1788528868 64
1788528873 64
1788528878 64
1788528883 64
1788528888 64
1788528893 64
1788528898 64
1788528903 64
1788528908 64
1788528913 64
```
</details>

---

