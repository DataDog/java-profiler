---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:33:02 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 73-82 cores)</summary>

```
1792977981 82
1792977986 73
1792977991 73
1792977996 73
1792978001 73
1792978006 73
1792978011 73
1792978016 73
1792978021 73
1792978026 73
1792978031 73
1792978036 73
1792978041 73
1792978046 73
1792978051 73
1792978056 73
1792978061 73
1792978066 73
1792978071 73
1792978076 73
```
</details>

---

