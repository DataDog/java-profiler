---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 07:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793101167 32
1793101172 32
1793101177 32
1793101182 32
1793101187 32
1793101192 32
1793101197 32
1793101202 32
1793101207 32
1793101212 32
1793101217 30
1793101222 30
1793101227 30
1793101232 30
1793101237 30
1793101242 30
1793101247 30
1793101252 30
1793101257 30
1793101262 30
```
</details>

---

