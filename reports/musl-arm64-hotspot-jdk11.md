---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:32:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794914888 38
1794914893 38
1794914898 38
1794914903 38
1794914908 38
1794914913 38
1794914918 38
1794914923 38
1794914928 51
1794914933 51
1794914938 51
1794914943 51
1794914948 51
1794914953 51
1794914958 51
1794914963 51
1794914968 51
1794914973 51
1794914978 51
1794914983 51
```
</details>

---

