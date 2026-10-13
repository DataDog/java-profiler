---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 973 |
| Sample Rate | 16.22/sec |
| Health Score | 1014% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1791908997 64
1791909002 64
1791909007 64
1791909012 64
1791909017 64
1791909022 64
1791909027 64
1791909032 64
1791909037 64
1791909042 64
1791909047 64
1791909052 64
1791909057 64
1791909062 64
1791909067 64
1791909072 64
1791909077 64
1791909082 59
1791909087 59
1791909092 59
```
</details>

---

