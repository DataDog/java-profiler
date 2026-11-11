---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 18:52:59 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 8 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1794440898 76
1794440903 76
1794440908 76
1794440913 76
1794440918 76
1794440923 96
1794440928 96
1794440933 96
1794440938 96
1794440943 96
1794440948 96
1794440953 96
1794440958 96
1794440963 96
1794440968 96
1794440973 96
1794440978 96
1794440983 94
1794440988 94
1794440993 94
```
</details>

---

