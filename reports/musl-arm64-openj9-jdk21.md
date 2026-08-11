---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 11:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 14 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1786462945 24
1786462950 24
1786462955 24
1786462960 24
1786462965 24
1786462970 24
1786462975 24
1786462980 24
1786462985 24
1786462990 24
1786462995 24
1786463000 24
1786463005 24
1786463010 24
1786463015 24
1786463020 24
1786463025 24
1786463030 24
1786463035 24
1786463040 19
```
</details>

---

