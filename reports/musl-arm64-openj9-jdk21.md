---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 06:43:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 15 |
| Allocations | 170 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794915517 38
1794915522 38
1794915527 38
1794915532 38
1794915537 38
1794915542 38
1794915547 38
1794915552 38
1794915557 38
1794915562 38
1794915567 38
1794915572 51
1794915577 51
1794915582 51
1794915587 51
1794915592 51
1794915597 51
1794915602 51
1794915607 51
1794915612 51
```
</details>

---

