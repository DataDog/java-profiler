---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:27:40 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1794392581 42
1794392586 42
1794392591 42
1794392596 42
1794392601 42
1794392606 42
1794392611 48
1794392616 48
1794392621 48
1794392626 48
1794392631 48
1794392636 48
1794392641 48
1794392646 48
1794392651 48
1794392656 48
1794392661 48
1794392666 48
1794392671 48
1794392676 48
```
</details>

---

