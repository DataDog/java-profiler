---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:43:59 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793101171 48
1793101176 48
1793101181 48
1793101186 48
1793101191 48
1793101196 48
1793101201 48
1793101206 48
1793101211 48
1793101216 48
1793101221 48
1793101226 48
1793101231 48
1793101236 48
1793101241 48
1793101246 48
1793101251 48
1793101256 48
1793101261 43
1793101266 43
```
</details>

---

