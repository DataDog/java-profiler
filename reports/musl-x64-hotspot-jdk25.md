---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 09:21:56 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1787059026 92
1787059031 92
1787059036 94
1787059041 94
1787059046 94
1787059051 94
1787059056 94
1787059061 86
1787059066 86
1787059071 86
1787059076 86
1787059081 86
1787059086 86
1787059091 86
1787059096 86
1787059101 86
1787059106 86
1787059111 86
1787059116 86
1787059121 86
```
</details>

---

