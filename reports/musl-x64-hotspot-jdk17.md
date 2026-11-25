---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 60-77 cores)</summary>

```
1795610857 75
1795610862 75
1795610867 77
1795610872 77
1795610878 71
1795610883 71
1795610888 71
1795610893 71
1795610898 71
1795610903 71
1795610908 62
1795610913 62
1795610918 60
1795610923 60
1795610928 60
1795610933 60
1795610938 60
1795610943 60
1795610948 60
1795610953 60
```
</details>

---

