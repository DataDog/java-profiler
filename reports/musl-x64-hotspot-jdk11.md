---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 09:49:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 47-72 cores)</summary>

```
1786023843 72
1786023848 72
1786023853 72
1786023858 72
1786023863 72
1786023868 72
1786023873 51
1786023878 51
1786023883 51
1786023888 51
1786023893 51
1786023898 51
1786023903 51
1786023908 51
1786023913 51
1786023918 51
1786023923 51
1786023928 51
1786023934 51
1786023939 51
```
</details>

---

