---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:13:49 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 45-66 cores)</summary>

```
1793614065 50
1793614070 50
1793614075 50
1793614080 50
1793614085 45
1793614090 45
1793614095 45
1793614100 45
1793614105 45
1793614110 45
1793614115 45
1793614120 45
1793614125 45
1793614130 45
1793614135 45
1793614140 45
1793614145 45
1793614150 45
1793614155 45
1793614160 45
```
</details>

---

