---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1787600224 20
1787600229 20
1787600234 20
1787600239 18
1787600244 18
1787600249 18
1787600254 18
1787600259 18
1787600264 18
1787600269 18
1787600274 18
1787600279 18
1787600284 18
1787600289 20
1787600294 20
1787600299 20
1787600304 20
1787600309 20
1787600314 20
1787600319 20
```
</details>

---

