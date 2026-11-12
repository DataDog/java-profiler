---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:45:39 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794480093 51
1794480098 51
1794480103 51
1794480108 51
1794480113 51
1794480118 51
1794480123 51
1794480128 51
1794480133 51
1794480138 51
1794480143 51
1794480148 51
1794480153 51
1794480158 51
1794480163 51
1794480168 51
1794480173 51
1794480178 51
1794480183 51
1794480188 51
```
</details>

---

