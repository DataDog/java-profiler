---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793721272 48
1793721277 48
1793721282 48
1793721287 48
1793721292 48
1793721297 48
1793721302 48
1793721307 48
1793721312 48
1793721317 48
1793721322 48
1793721327 48
1793721332 48
1793721337 48
1793721342 48
1793721347 48
1793721352 48
1793721357 48
1793721362 48
1793721367 48
```
</details>

---

