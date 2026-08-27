---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-27 08:58:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1787835203 64
1787835208 64
1787835213 64
1787835218 64
1787835223 64
1787835228 64
1787835233 64
1787835238 64
1787835243 64
1787835248 54
1787835253 54
1787835258 54
1787835263 54
1787835268 54
1787835273 54
1787835278 54
1787835283 54
1787835288 54
1787835293 54
1787835298 54
```
</details>

---

