---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-08 06:01:09 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 14-21 cores)</summary>

```
1794135080 19
1794135085 19
1794135090 21
1794135095 21
1794135100 21
1794135105 21
1794135110 21
1794135115 21
1794135120 21
1794135125 21
1794135130 21
1794135135 21
1794135140 21
1794135145 21
1794135150 21
1794135155 21
1794135160 14
1794135165 14
1794135170 14
1794135175 14
```
</details>

---

