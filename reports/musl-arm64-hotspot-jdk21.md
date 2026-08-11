---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 11:48:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1786462960 22
1786462965 27
1786462970 27
1786462975 27
1786462980 27
1786462985 27
1786462990 27
1786462995 27
1786463000 27
1786463005 27
1786463010 27
1786463015 27
1786463020 27
1786463025 27
1786463030 27
1786463035 22
1786463040 22
1786463045 22
1786463050 22
1786463056 22
```
</details>

---

