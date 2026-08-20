---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 08:51:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 91-94 cores)</summary>

```
1787229976 93
1787229981 93
1787229986 93
1787229991 93
1787229996 93
1787230001 93
1787230006 93
1787230011 93
1787230016 93
1787230021 93
1787230026 91
1787230031 91
1787230036 91
1787230041 91
1787230046 91
1787230051 91
1787230056 91
1787230061 91
1787230066 94
1787230071 94
```
</details>

---

