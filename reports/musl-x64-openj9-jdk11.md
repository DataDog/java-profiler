---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 07:44:00 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 72-85 cores)</summary>

```
1793101146 85
1793101151 85
1793101156 85
1793101161 85
1793101166 85
1793101171 85
1793101176 76
1793101181 76
1793101186 76
1793101191 76
1793101196 76
1793101201 76
1793101206 76
1793101211 76
1793101216 76
1793101221 76
1793101226 76
1793101231 76
1793101236 76
1793101241 76
```
</details>

---

