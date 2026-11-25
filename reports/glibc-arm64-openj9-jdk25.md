---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:23:45 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 11 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795627228 64
1795627233 64
1795627238 64
1795627243 64
1795627248 64
1795627253 64
1795627258 64
1795627263 64
1795627268 64
1795627273 64
1795627278 64
1795627283 64
1795627288 64
1795627293 64
1795627298 64
1795627303 64
1795627308 64
1795627313 64
1795627318 64
1795627323 64
```
</details>

---

