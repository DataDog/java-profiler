---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 13 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786376072 53
1786376077 53
1786376082 53
1786376087 53
1786376092 53
1786376097 53
1786376102 53
1786376107 53
1786376112 53
1786376117 53
1786376122 53
1786376127 53
1786376132 53
1786376137 53
1786376142 53
1786376147 53
1786376152 53
1786376157 53
1786376162 53
1786376167 53
```
</details>

---

