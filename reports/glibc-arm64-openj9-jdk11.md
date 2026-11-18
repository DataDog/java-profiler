---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:50:18 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 39-59 cores)</summary>

```
1795031163 39
1795031168 39
1795031173 39
1795031178 39
1795031183 39
1795031188 39
1795031193 39
1795031198 39
1795031203 39
1795031208 39
1795031213 39
1795031218 39
1795031223 39
1795031228 39
1795031233 39
1795031238 59
1795031243 59
1795031248 59
1795031253 59
1795031258 59
```
</details>

---

