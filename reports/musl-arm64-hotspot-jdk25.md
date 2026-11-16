---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:31:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794824823 51
1794824828 51
1794824833 51
1794824838 51
1794824843 51
1794824848 51
1794824853 51
1794824858 51
1794824863 51
1794824868 51
1794824873 51
1794824878 51
1794824883 51
1794824888 51
1794824893 51
1794824898 51
1794824903 51
1794824908 51
1794824913 51
1794824918 51
```
</details>

---

