---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 06:47:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 40-44 cores)</summary>

```
1794310986 44
1794310991 44
1794310996 44
1794311001 44
1794311006 44
1794311011 44
1794311016 44
1794311021 44
1794311026 44
1794311031 40
1794311036 40
1794311041 40
1794311046 40
1794311051 40
1794311056 40
1794311061 40
1794311066 40
1794311071 40
1794311076 40
1794311081 40
```
</details>

---

