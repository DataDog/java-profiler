---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-28 10:31:45 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 9 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787927216 43
1787927221 43
1787927226 43
1787927231 43
1787927236 43
1787927241 43
1787927246 43
1787927251 43
1787927256 43
1787927261 43
1787927266 43
1787927271 48
1787927276 48
1787927281 48
1787927286 43
1787927291 43
1787927296 43
1787927301 43
1787927306 43
1787927311 43
```
</details>

---

