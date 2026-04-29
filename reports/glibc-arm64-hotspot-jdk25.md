---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 11 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777475051 64
1777475056 64
1777475061 64
1777475066 64
1777475071 64
1777475076 64
1777475081 64
1777475086 59
1777475091 59
1777475096 59
1777475101 59
1777475106 59
1777475111 59
1777475116 59
1777475121 59
1777475126 59
1777475131 59
1777475136 59
1777475141 59
1777475146 59
```
</details>

---

