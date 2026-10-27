---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:43:58 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 70-84 cores)</summary>

```
1793101189 81
1793101194 84
1793101199 84
1793101204 84
1793101209 75
1793101214 75
1793101219 75
1793101224 75
1793101229 75
1793101234 75
1793101239 75
1793101244 75
1793101249 70
1793101254 70
1793101259 70
1793101264 70
1793101269 70
1793101274 70
1793101279 70
1793101284 70
```
</details>

---

