---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 07:43:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 70-84 cores)</summary>

```
1793101171 81
1793101176 81
1793101181 81
1793101186 81
1793101191 81
1793101196 84
1793101201 84
1793101206 75
1793101211 75
1793101216 75
1793101221 75
1793101226 75
1793101231 75
1793101236 75
1793101241 75
1793101246 75
1793101251 70
1793101256 70
1793101261 70
1793101266 70
```
</details>

---

