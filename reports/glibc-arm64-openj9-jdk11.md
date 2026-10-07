---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 17:27:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791408198 48
1791408203 48
1791408208 48
1791408213 48
1791408218 43
1791408223 43
1791408228 43
1791408233 43
1791408238 43
1791408243 43
1791408248 43
1791408253 43
1791408258 48
1791408263 48
1791408268 48
1791408273 48
1791408278 48
1791408283 48
1791408288 48
1791408293 48
```
</details>

---

