---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 15:10:51 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 12 |
| Allocations | 224 |

<details>
<summary>CPU Timeline (2 unique values: 20-23 cores)</summary>

```
1792523067 23
1792523072 23
1792523077 23
1792523082 23
1792523087 23
1792523092 23
1792523097 23
1792523102 23
1792523107 23
1792523112 23
1792523117 23
1792523122 23
1792523127 23
1792523132 23
1792523137 23
1792523142 23
1792523147 20
1792523152 20
1792523157 20
1792523162 20
```
</details>

---

