---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:50:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 21-52 cores)</summary>

```
1795628797 33
1795628802 33
1795628807 33
1795628813 33
1795628818 33
1795628823 33
1795628828 33
1795628833 33
1795628838 33
1795628843 33
1795628848 33
1795628853 33
1795628858 33
1795628863 33
1795628868 33
1795628873 33
1795628878 33
1795628883 33
1795628888 33
1795628893 33
```
</details>

---

