---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 10:07:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770130847 32
1770130852 32
1770130857 32
1770130862 32
1770130867 32
1770130872 32
1770130877 30
1770130882 30
1770130887 30
1770130892 30
1770130897 30
1770130902 30
1770130907 32
1770130912 32
1770130917 32
1770130922 32
1770130927 32
1770130932 32
1770130937 32
1770130942 32
```
</details>

---

