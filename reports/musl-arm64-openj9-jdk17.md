---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 17:27:41 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1791408163 40
1791408168 40
1791408173 40
1791408178 40
1791408183 40
1791408188 40
1791408193 38
1791408198 38
1791408203 38
1791408208 38
1791408213 38
1791408218 38
1791408223 38
1791408228 38
1791408233 38
1791408238 38
1791408243 38
1791408248 38
1791408253 38
1791408258 38
```
</details>

---

