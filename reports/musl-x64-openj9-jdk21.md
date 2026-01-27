---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 21.43/sec |
| Health Score | 1339% |
| Threads | 11 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 27.47/sec |
| Health Score | 1717% |
| Threads | 13 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 68-76 cores)</summary>

```
1769526911 68
1769526916 68
1769526921 71
1769526926 71
1769526931 71
1769526936 71
1769526941 71
1769526946 71
1769526951 71
1769526956 71
1769526961 71
1769526966 71
1769526971 71
1769526976 71
1769526981 71
1769526986 71
1769526991 74
1769526996 74
1769527001 76
1769527006 76
```
</details>

---

