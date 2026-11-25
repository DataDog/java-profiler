---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:23:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 11 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 14 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795627067 64
1795627072 64
1795627077 64
1795627082 64
1795627087 64
1795627092 64
1795627097 64
1795627102 64
1795627107 47
1795627112 47
1795627117 47
1795627122 47
1795627127 47
1795627132 47
1795627137 47
1795627142 47
1795627147 47
1795627152 47
1795627157 47
1795627162 47
```
</details>

---

