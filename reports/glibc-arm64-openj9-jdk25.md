---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 20:55:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777510282 64
1777510287 64
1777510292 64
1777510297 64
1777510302 64
1777510307 64
1777510312 64
1777510317 64
1777510322 64
1777510327 64
1777510332 64
1777510337 64
1777510342 59
1777510347 59
1777510352 59
1777510357 59
1777510362 59
1777510367 59
1777510372 59
1777510377 59
```
</details>

---

