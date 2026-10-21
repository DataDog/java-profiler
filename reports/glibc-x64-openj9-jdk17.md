---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 10:48:10 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 403 |

<details>
<summary>CPU Timeline (2 unique values: 87-89 cores)</summary>

```
1792593788 89
1792593793 89
1792593798 89
1792593803 89
1792593808 87
1792593813 87
1792593818 87
1792593823 87
1792593828 87
1792593833 87
1792593838 87
1792593843 87
1792593848 87
1792593853 87
1792593858 87
1792593863 87
1792593868 87
1792593873 89
1792593878 89
1792593883 89
```
</details>

---

