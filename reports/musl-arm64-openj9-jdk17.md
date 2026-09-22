---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:34:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 10 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790094178 49
1790094183 49
1790094188 49
1790094193 64
1790094198 64
1790094203 64
1790094208 49
1790094213 49
1790094218 49
1790094223 49
1790094228 49
1790094233 49
1790094238 49
1790094243 49
1790094248 49
1790094253 49
1790094258 49
1790094263 49
1790094268 49
1790094273 49
```
</details>

---

