---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:22:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1795025848 92
1795025853 92
1795025858 92
1795025863 90
1795025868 90
1795025873 90
1795025878 90
1795025883 90
1795025888 90
1795025893 90
1795025898 90
1795025903 90
1795025908 92
1795025913 92
1795025918 94
1795025923 94
1795025928 94
1795025933 94
1795025938 94
1795025943 94
```
</details>

---

