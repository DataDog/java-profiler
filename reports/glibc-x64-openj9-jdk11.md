---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 09:21:53 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1787059032 92
1787059037 92
1787059042 94
1787059047 94
1787059052 94
1787059057 92
1787059062 92
1787059067 92
1787059072 92
1787059077 90
1787059082 90
1787059087 90
1787059092 90
1787059097 90
1787059102 90
1787059107 90
1787059112 88
1787059117 88
1787059122 88
1787059127 88
```
</details>

---

