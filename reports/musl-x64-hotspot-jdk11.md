---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:53:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 36-39 cores)</summary>

```
1795106912 39
1795106917 39
1795106922 39
1795106927 39
1795106932 39
1795106937 39
1795106942 39
1795106947 39
1795106952 39
1795106957 39
1795106962 39
1795106967 39
1795106972 39
1795106977 39
1795106982 39
1795106987 39
1795106992 39
1795106997 39
1795107002 36
1795107007 36
```
</details>

---

