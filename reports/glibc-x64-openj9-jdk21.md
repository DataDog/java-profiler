---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:24:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 57-83 cores)</summary>

```
1795195223 57
1795195228 57
1795195233 76
1795195238 76
1795195243 83
1795195248 83
1795195253 83
1795195258 83
1795195263 83
1795195268 83
1795195273 83
1795195278 83
1795195283 83
1795195288 83
1795195293 83
1795195298 79
1795195303 79
1795195308 79
1795195313 79
1795195318 79
```
</details>

---

