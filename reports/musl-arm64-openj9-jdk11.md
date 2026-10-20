---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 14:20:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1003 |
| Sample Rate | 16.72/sec |
| Health Score | 1045% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1792520056 30
1792520061 30
1792520066 30
1792520071 30
1792520076 30
1792520081 30
1792520086 30
1792520091 30
1792520096 30
1792520101 30
1792520106 30
1792520111 30
1792520116 30
1792520121 30
1792520126 30
1792520131 35
1792520136 35
1792520141 35
1792520146 35
1792520151 35
```
</details>

---

