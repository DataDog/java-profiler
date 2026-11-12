---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:55:46 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794484085 43
1794484090 43
1794484095 43
1794484100 43
1794484105 43
1794484110 43
1794484115 43
1794484120 43
1794484125 43
1794484130 43
1794484135 43
1794484140 48
1794484145 48
1794484150 48
1794484155 48
1794484160 48
1794484165 48
1794484170 48
1794484175 48
1794484180 48
```
</details>

---

