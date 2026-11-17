---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 06:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 14 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794914893 51
1794914898 51
1794914903 51
1794914908 51
1794914913 51
1794914918 51
1794914923 51
1794914928 51
1794914933 51
1794914938 51
1794914943 51
1794914948 51
1794914953 51
1794914958 51
1794914963 51
1794914968 51
1794914973 46
1794914978 46
1794914983 46
1794914988 46
```
</details>

---

