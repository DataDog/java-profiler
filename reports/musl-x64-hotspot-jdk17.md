---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:56:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 30-34 cores)</summary>

```
1795171818 32
1795171823 32
1795171828 32
1795171833 32
1795171838 30
1795171843 30
1795171848 30
1795171853 30
1795171858 30
1795171863 30
1795171868 30
1795171873 30
1795171878 30
1795171883 30
1795171888 34
1795171893 34
1795171898 34
1795171903 34
1795171908 34
1795171913 34
```
</details>

---

