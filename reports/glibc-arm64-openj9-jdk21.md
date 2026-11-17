---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:48:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794930063 51
1794930068 51
1794930073 51
1794930078 51
1794930083 51
1794930088 51
1794930093 51
1794930098 51
1794930103 51
1794930108 51
1794930113 51
1794930118 46
1794930123 46
1794930128 46
1794930133 46
1794930138 46
1794930143 46
1794930148 46
1794930153 46
1794930158 46
```
</details>

---

