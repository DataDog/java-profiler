---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 24.73/sec |
| Health Score | 1546% |
| Threads | 11 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 935 |
| Sample Rate | 31.17/sec |
| Health Score | 1948% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 79-88 cores)</summary>

```
1769526906 88
1769526911 88
1769526916 88
1769526921 88
1769526926 88
1769526931 88
1769526936 88
1769526941 88
1769526946 88
1769526951 79
1769526956 79
1769526961 79
1769526966 79
1769526971 79
1769526976 79
1769526981 79
1769526986 79
1769526991 79
1769526996 79
1769527001 79
```
</details>

---

