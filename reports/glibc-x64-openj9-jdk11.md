---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:46:28 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1778582412 43
1778582417 43
1778582422 43
1778582427 43
1778582432 43
1778582437 45
1778582442 45
1778582447 45
1778582452 45
1778582457 45
1778582462 45
1778582467 45
1778582472 45
1778582477 45
1778582482 45
1778582487 45
1778582492 45
1778582497 45
1778582502 45
1778582507 45
```
</details>

---

