---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 14:47:37 EST

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
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794512593 48
1794512598 48
1794512603 48
1794512608 48
1794512613 48
1794512618 48
1794512623 48
1794512628 48
1794512633 48
1794512638 48
1794512643 48
1794512648 48
1794512653 48
1794512658 48
1794512663 48
1794512668 48
1794512673 48
1794512678 48
1794512683 48
1794512688 48
```
</details>

---

