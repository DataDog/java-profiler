---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 08:47:50 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 10 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1794922822 92
1794922827 92
1794922832 92
1794922837 92
1794922842 92
1794922847 92
1794922852 92
1794922857 92
1794922863 92
1794922868 92
1794922873 92
1794922878 92
1794922883 92
1794922888 92
1794922893 92
1794922898 90
1794922903 90
1794922908 90
1794922913 90
1794922918 90
```
</details>

---

