---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 08:18:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793362373 48
1793362378 48
1793362383 48
1793362388 48
1793362393 48
1793362398 43
1793362403 43
1793362408 43
1793362413 43
1793362418 43
1793362423 43
1793362428 43
1793362433 43
1793362438 43
1793362443 43
1793362448 43
1793362453 43
1793362458 43
1793362463 43
1793362468 43
```
</details>

---

