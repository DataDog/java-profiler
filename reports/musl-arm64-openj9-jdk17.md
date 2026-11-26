---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

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
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795691151 64
1795691156 64
1795691161 64
1795691166 64
1795691171 64
1795691176 64
1795691181 64
1795691186 33
1795691191 33
1795691196 33
1795691201 33
1795691206 33
1795691211 33
1795691216 33
1795691221 33
1795691226 33
1795691231 33
1795691236 33
1795691241 33
1795691246 33
```
</details>

---

