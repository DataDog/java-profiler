---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:22:06 EDT

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
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 11 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788139129 64
1788139134 64
1788139139 64
1788139144 64
1788139149 64
1788139154 64
1788139159 64
1788139164 64
1788139169 64
1788139174 64
1788139179 64
1788139184 64
1788139189 64
1788139194 64
1788139199 64
1788139204 64
1788139209 64
1788139214 64
1788139219 64
1788139224 64
```
</details>

---

