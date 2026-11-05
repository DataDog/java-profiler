---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 8 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793890203 30
1793890208 30
1793890213 30
1793890218 30
1793890223 30
1793890228 30
1793890233 32
1793890238 32
1793890243 30
1793890248 30
1793890253 30
1793890258 30
1793890263 30
1793890268 30
1793890273 30
1793890278 30
1793890283 30
1793890288 30
1793890293 30
1793890298 30
```
</details>

---

