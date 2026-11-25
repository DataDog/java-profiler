---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:49:49 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1795621542 83
1795621547 83
1795621552 83
1795621557 83
1795621562 83
1795621567 83
1795621572 85
1795621577 85
1795621582 83
1795621587 83
1795621592 81
1795621597 81
1795621602 81
1795621607 81
1795621612 81
1795621617 81
1795621622 81
1795621627 81
1795621632 81
1795621637 81
```
</details>

---

