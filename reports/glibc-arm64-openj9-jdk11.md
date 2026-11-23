---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:16:16 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 12 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795432137 64
1795432142 64
1795432147 59
1795432152 59
1795432157 59
1795432162 59
1795432167 59
1795432172 59
1795432177 59
1795432182 59
1795432187 59
1795432192 59
1795432197 59
1795432202 59
1795432207 64
1795432212 64
1795432217 64
1795432222 64
1795432227 64
1795432232 64
```
</details>

---

