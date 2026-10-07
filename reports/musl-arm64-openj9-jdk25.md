---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 10:29:48 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 12 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791383016 43
1791383021 43
1791383026 43
1791383032 43
1791383037 43
1791383042 43
1791383047 43
1791383052 43
1791383057 43
1791383062 43
1791383067 43
1791383072 48
1791383077 48
1791383082 48
1791383087 48
1791383092 48
1791383097 48
1791383102 43
1791383107 43
1791383112 43
```
</details>

---

