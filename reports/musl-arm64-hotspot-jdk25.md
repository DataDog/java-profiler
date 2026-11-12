---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794495903 51
1794495908 51
1794495913 51
1794495918 51
1794495923 51
1794495928 51
1794495933 51
1794495938 51
1794495943 51
1794495948 51
1794495953 51
1794495958 51
1794495963 51
1794495968 64
1794495973 64
1794495978 51
1794495983 51
1794495988 51
1794495993 51
1794495998 51
```
</details>

---

