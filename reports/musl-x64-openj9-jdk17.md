---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:44:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1793101139 48
1793101144 48
1793101149 48
1793101154 48
1793101159 48
1793101164 48
1793101169 48
1793101174 48
1793101179 48
1793101184 39
1793101189 39
1793101194 39
1793101199 39
1793101204 39
1793101209 39
1793101214 39
1793101219 39
1793101224 39
1793101229 39
1793101234 39
```
</details>

---

