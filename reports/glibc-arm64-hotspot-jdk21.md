---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 11:48:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 13 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786462950 32
1786462955 32
1786462960 32
1786462965 32
1786462970 32
1786462975 32
1786462980 32
1786462985 32
1786462990 32
1786462995 32
1786463000 32
1786463005 32
1786463010 32
1786463015 32
1786463020 32
1786463025 32
1786463030 32
1786463035 32
1786463040 32
1786463045 32
```
</details>

---

