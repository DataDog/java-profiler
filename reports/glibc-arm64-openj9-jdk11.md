---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:05:41 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 13 |
| Allocations | 176 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1789682112 43
1789682117 43
1789682122 43
1789682127 43
1789682132 38
1789682137 38
1789682142 38
1789682147 38
1789682152 38
1789682157 38
1789682162 38
1789682167 38
1789682172 33
1789682177 33
1789682182 33
1789682187 33
1789682192 33
1789682198 33
1789682203 33
1789682208 33
```
</details>

---

