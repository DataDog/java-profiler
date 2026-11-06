---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 16:43:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794001159 64
1794001164 64
1794001169 64
1794001174 64
1794001179 64
1794001184 64
1794001189 64
1794001194 64
1794001199 64
1794001204 64
1794001209 64
1794001214 64
1794001219 64
1794001224 64
1794001229 64
1794001234 64
1794001239 64
1794001244 64
1794001249 64
1794001254 64
```
</details>

---

