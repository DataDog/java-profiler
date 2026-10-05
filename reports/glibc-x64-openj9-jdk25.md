---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 11:50:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1791215152 96
1791215157 96
1791215162 96
1791215167 96
1791215172 96
1791215177 96
1791215182 94
1791215187 94
1791215192 94
1791215197 94
1791215202 94
1791215207 94
1791215212 94
1791215217 94
1791215222 94
1791215227 94
1791215232 94
1791215237 94
1791215242 94
1791215247 96
```
</details>

---

