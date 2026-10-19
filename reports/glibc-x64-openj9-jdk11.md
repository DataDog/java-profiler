---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 18:19:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1792448077 32
1792448082 32
1792448087 32
1792448092 32
1792448097 32
1792448102 32
1792448107 32
1792448112 32
1792448117 32
1792448122 32
1792448127 32
1792448132 32
1792448137 32
1792448142 32
1792448147 32
1792448152 32
1792448157 30
1792448162 30
1792448167 30
1792448172 30
```
</details>

---

