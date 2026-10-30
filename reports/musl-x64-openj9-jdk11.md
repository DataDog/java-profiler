---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 17:09:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793394250 32
1793394255 32
1793394260 32
1793394265 32
1793394270 32
1793394275 32
1793394280 32
1793394285 32
1793394290 32
1793394295 32
1793394300 32
1793394305 32
1793394310 32
1793394315 32
1793394320 32
1793394325 32
1793394330 32
1793394335 32
1793394340 32
1793394345 32
```
</details>

---

