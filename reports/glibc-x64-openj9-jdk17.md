---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 69-92 cores)</summary>

```
1793742174 92
1793742179 92
1793742184 92
1793742189 92
1793742194 92
1793742199 92
1793742204 92
1793742209 92
1793742214 92
1793742219 92
1793742224 92
1793742229 92
1793742234 92
1793742239 92
1793742244 69
1793742249 69
1793742254 69
1793742259 69
1793742264 69
1793742269 69
```
</details>

---

