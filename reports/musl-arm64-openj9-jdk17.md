---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 10:05:16 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 10 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 10 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1793023150 36
1793023155 36
1793023160 36
1793023165 36
1793023170 36
1793023175 36
1793023180 36
1793023185 41
1793023190 41
1793023195 41
1793023200 41
1793023205 43
1793023210 43
1793023215 43
1793023220 43
1793023225 48
1793023230 48
1793023235 48
1793023240 48
1793023245 48
```
</details>

---

