---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 13:09:37 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 57-90 cores)</summary>

```
1791306164 57
1791306169 57
1791306174 57
1791306179 57
1791306184 57
1791306189 57
1791306194 57
1791306199 57
1791306204 57
1791306209 57
1791306214 57
1791306219 57
1791306224 57
1791306229 57
1791306234 57
1791306239 57
1791306244 90
1791306249 90
1791306254 90
1791306259 63
```
</details>

---

