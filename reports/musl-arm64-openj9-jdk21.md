---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-03 04:34:58 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 42-59 cores)</summary>

```
1791016238 42
1791016243 42
1791016248 42
1791016253 42
1791016258 47
1791016263 47
1791016268 47
1791016273 47
1791016278 54
1791016283 54
1791016288 54
1791016293 54
1791016298 54
1791016303 54
1791016308 54
1791016313 54
1791016318 54
1791016323 54
1791016328 54
1791016333 54
```
</details>

---

