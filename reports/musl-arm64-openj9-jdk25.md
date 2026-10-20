---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 13:18:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792516408 51
1792516413 51
1792516418 51
1792516423 51
1792516428 51
1792516433 51
1792516438 51
1792516443 51
1792516448 51
1792516453 51
1792516458 51
1792516463 51
1792516468 51
1792516473 51
1792516478 51
1792516483 51
1792516488 51
1792516493 51
1792516498 39
1792516503 39
```
</details>

---

